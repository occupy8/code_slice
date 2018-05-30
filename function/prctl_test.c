/**
  * change progress's name  
  * ps -p <pid>
  *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <unistd.h>

int run(const char *name) {
	prctl(PR_SET_NAME, name);
	
	return 0;
}

int main(void) {
	run("prctl_test_haha");

	while(1)
		sleep(10);
	
	return 0;
}
