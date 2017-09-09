#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>
#include <assert.h>

#define     SO_REUSEPORT            15
#define     MAXBUF               10240
#define     MAXEPOLLSIZE         1000

int flag = 0;

int read_data(int sd)
{
	char recvbuf[MAXBUF + 1];
	int ret;
	struct sockaddr_in client_addr;
	socklen_t cli_len = sizeof(client_addr);
	
	bzero(recvbuf, MAXBUF+1);
	
	ret = recvfrom(sd, recvbuf, MAXBUF, 0, (struct sockaddr *)&client_addr, &cli_len);
	if(ret > 0){
		printf("read[%d]: %s from ip:%s, port:%d\n", ret, recvbuf, inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
		sendto(sd, recvbuf, ret, 0, (struct sockaddr *)&client_addr, cli_len);
	}
	else{
		printf("read err:%s %d\n", strerror(errno), ret);
	}

	fflush(stdout);

	return 0;
}

int udp_accept(int sd, struct sockaddr_in my_addr){
	int new_sd = -1;
	int ret = 0;
	int reuse = 1;
	char buf[16];
	struct sockaddr_in peer_addr;
	socklen_t cli_len = sizeof(peer_addr);

	ret = recvfrom(sd, buf, 16, 0, (struct sockaddr *)&peer_addr, &cli_len);
	if(ret > 0){

	}

	if((new_sd = socket(PF_INET, SOCK_DGRAM, 0)) == -1){
		perror("child socket");
		exit(1);
	}else{
		printf("parent:%d new:%d\n", sd, new_sd);	
	}

	ret = setsockopt(new_sd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	if(ret){
		exit(1);
	}

	ret = setsockopt(new_sd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
	if(ret){
		exit(1);
	}

	ret = bind(new_sd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
	if(ret){
		perror("chid bind");
		exit(1);
	}else{

	}
	peer_addr.sin_family = PF_INET;
	printf("ip:%s\n", inet_ntoa(peer_addr.sin_addr));
	if(connect(new_sd, (struct sockaddr *)&peer_addr, sizeof(struct sockaddr)) == -1){
		perror("chid connect");
		exit(1);
	}
	else{
		
	}
	
out:
	return new_sd;
}

static void add_event(int epollfd, int fd, int state){
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}
static void delete_event(int epollfd, int fd, int state){
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

static void modify_event(int epollfd, int fd, int state){
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

int main(int argc, char **argv)  
{  
    int listener, kdpfd, nfds, n, curfds;  
    socklen_t len;  
    struct sockaddr_in my_addr, their_addr;  
    unsigned int port;  
    struct epoll_event ev;  
    struct epoll_event events[MAXEPOLLSIZE];  
    int opt = 1;;  
    int ret = 0;  
  
    port = 1234;  
    
    if ((listener = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {  
        perror("socket");  
        exit(1);  
    } else {  
        printf("socket OK\n");  
    }  
  
    ret = setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));  
    if (ret) {  
        exit(1);  
    }  
  
    ret = setsockopt(listener, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));  
    if (ret) {  
        exit(1);  
    }  
    
    bzero(&my_addr, sizeof(my_addr));  
    my_addr.sin_family = PF_INET;  
    my_addr.sin_port = htons(port);  
    my_addr.sin_addr.s_addr = INADDR_ANY;  
    if (bind(listener, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) {  
        perror("bind");  
        exit(1);  
    } else {  
        printf("IP bind OK\n");  
    }  
    
    kdpfd = epoll_create(MAXEPOLLSIZE);  
  
    ev.events = EPOLLIN|EPOLLET;  
    ev.data.fd = listener;  
  
    if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, listener, &ev) < 0) {  
        fprintf(stderr, "epoll set insertion error: fd=%dn", listener);  
        return -1;  
    } else {  
        printf("ep add OK\n");  
    }  
   
    while (1) {  
        
        nfds = epoll_wait(kdpfd, events, MAXEPOLLSIZE, -1);  
        if (nfds == -1) {  
            perror("epoll_wait");  
            break;  
        }  
        
        for (n = 0; n < nfds; ++n) {  
            if ((events[n].data.fd == listener) && (events[n].events & EPOLLIN)) {  
                printf("listener:%d\n", n);  
                int new_sd;                 
                struct epoll_event child_ev;  
  
                new_sd = udp_accept(listener, my_addr);  
                child_ev.events = EPOLLIN|EPOLLRDHUP;  
                child_ev.data.fd = new_sd;  
                if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, new_sd, &child_ev) < 0) {  
                    fprintf(stderr, "epoll set insertion error: fd=%dn", new_sd);  
                    return -1;  
                }  
	    } else if(events[n].events & EPOLLRDHUP){
               	printf("something error happenned\n"); 
            } else if(events[n].events & EPOLLIN){
                read_data(events[n].data.fd);  
	    } else if(events[n].events & EPOLLOUT){  
		
	    }
        }  
    }  

    close(listener);  

    return 0;  
} 
