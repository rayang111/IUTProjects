#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	pid_t pid;
	int i;
	if (argc < 2) {
		perror("Pas assez d'arguments");
		return EXIT_FAILURE;
	}
	if (argc > 9) {
		perror("Trop d'arguments");
		return EXIT_FAILURE;
	}
	pid = fork();
	
	if (pid==0) {
		printf("pid de mon papa : %d\n", getppid());
		execvp(argv[1], argv+1);
		
	} else {
		printf("pid de mon fiston : %d\n", pid);
		wait(NULL);
		
	}
	return EXIT_SUCCESS;
}