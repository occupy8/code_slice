#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 1024 
#define SERV_PORT 8862 

void do_cli(int sockfd, struct sockaddr *pservaddr, socklen_t servlen)
{
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];
	if(connect(sockfd, (struct sockaddr *)pservaddr, servlen) == -1)
	{
		perror("connect error");
		exit(1);
	}
	strcpy(sendline, "hello world!");

	while(1)
	{
		write(sockfd, sendline, strlen(sendline));
        
		n = read(sockfd, recvline, MAXLINE);
		if(n == -1)
		{
			perror("read error");
			exit(1);
		}
        recvline[n] = '\0';

		printf("%s\n", recvline);
		sleep(5);
	}
}

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	if(argc != 3)
	{
		printf("usage: udpclient <ip> <port>\n");
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	{
		printf("[%s] is not a valid IPaddress\n", argv[1]);
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	do_cli(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	return 0;
} 
