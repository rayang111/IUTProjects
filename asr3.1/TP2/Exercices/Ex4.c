#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	pid_t pid = fork();
	if (pid == 0) {
	printf("Mon père est %d\n", getppid());
	sleep(0.2);
	printf("Mon nouveau père est %d\n", getppid());
	}
	sleep(0.1);
	
	return EXIT_SUCCESS;
}