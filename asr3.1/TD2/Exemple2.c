/* fork2b.c            */


#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	int i, n = 5;
	pid_t childpid;
	
	for (i=0; i<n; i++) {
		if ((childpid = fork()) == -1) break;
		if (childpid == 0)
		printf("Processus %d avec pere %d, i = %d\n", getpid(), getppid(), i);
	}
	
	while (wait(NULL) >= 0)
		;
		
	return EXIT_SUCCESS;
}
