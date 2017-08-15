#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
#define MAXLINE  1024 
 
int main(int argc, char *argv[])
{
     struct sockaddr_in servaddr, cliaddr;
     socklen_t cliaddr_len;
     int sockfd;
     char buf[MAXLINE];
     char str[INET_ADDRSTRLEN];
     int i, len;

     if(argc < 1){
         printf("./exe port");
         return 1;
     }

     int port = atoi(argv[1]);
 
     sockfd = socket(AF_INET, SOCK_DGRAM, 0);
 
     bzero(&servaddr, sizeof(servaddr));
     servaddr.sin_family = AF_INET;
     servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
     servaddr.sin_port = htons(port);
 
     bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
     printf("Accepting connections ...\n");
 
     while(1)
     {
         cliaddr_len = sizeof(cliaddr);
         len = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr*)&cliaddr, &cliaddr_len);
         if(len == -1)
         {
             printf("recvfrom error\n");
             continue;
         }
         printf("received from %s at PORT %d\n",
                         inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
                         ntohs(cliaddr.sin_port));
     }

     close(sockfd);

     return 0;
}
