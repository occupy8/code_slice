#define  _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]){
	int cpus = 0;
	int i = 0;
	cpu_set_t mask;
	cpu_set_t get;

	cpus = sysconf(_SC_NPROCESSORS_CONF);
	printf("cpus: %d\n", cpus);

	CPU_ZERO(&mask);
	CPU_SET(0, &mask);
	CPU_SET(1, &mask);

	/* 设置cpu亲和性*/
	if(sched_setaffinity(0, sizeof(mask), &mask) == -1){
		printf("set CPU affinity failur, ERROR:%s\n", strerror(errno));
		return -1;
	}

	usleep(1000);
	CPU_ZERO(&get);
	if(sched_getaffinity(0, sizeof(get), &get) == -1){
		printf("get CPU affinity failur, ERROR:%s\n", strerror(errno));
		return -1;
	}
	for(i = 0; i < cpus; i++){
		if(CPU_ISSET(i, &get)){
			printf("this process %d of running processor:%d\n", getpid(), i);
		}
	}

	sleep(3);

	return 0;
}
