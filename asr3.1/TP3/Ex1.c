#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
	pid_t pid;
	pid = fork();
	char *lel[3] = {"ls", "-l", NULL};
	if (pid==0) {
		printf("pid de mon papa : %d\n", getppid());
		execvp("ls", lel);
		
	} else {
		printf("pid de mon fiston : %d\n", pid);
		wait(NULL);
		
	}
	return EXIT_SUCCESS;
}