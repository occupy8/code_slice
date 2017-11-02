#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

typedef unsigned int uint_t;

int main(int argc, char *argv[])
{
	mqd_t mqd;
	char ptr[1024];
	size_t len;
	uint_t prio;
	if(argc != 4){
		printf("usage:mqsend <name> <msg> <priority>\n");
		exit(0);
	}

	prio = atoi(argv[3]);
	mqd = mq_open(argv[1], O_WRONLY);
	len = strlen(argv[2]);
	snprintf(ptr, sizeof(ptr), "%s", argv[2]);

	if(mq_send(mqd, ptr, len, prio) == -1)
	{
		perror("mq_send() error");
		exit(-1);	
	}

	exit(0);
}
