#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	
	int n = 5;
	pid_t fils_pid;
	
	for (int i=0; i < n; i++) {
		fils_pid = fork();
		
		if (fils_pid > 0) break;
		
		printf("Processus %d avec père %d  n=%d\n", getpid(), getppid(),i);
		
	}
	return EXIT_SUCCESS;
}
