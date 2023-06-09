#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
	pid_t first,pid1,pid2;
	if (!(pid1=fork())) {
		execlp("ls", "ls", "-l", NULL);
		return EXIT_SUCCESS;
	} 
	if (!(pid2=fork())) {
		execlp("ps", "ps", "-l", NULL);
		return EXIT_SUCCESS;
	}
	first = wait(NULL);
	wait(NULL); // On attend que le second fils finnisse
	printf("\nLe premier processus à s'être terminé est %d\n", first);
	if(pid1==first) {
		printf("C'est à dire le processus qui execute la commande \"ls -l\"\n", wait(NULL));
	} else {
		printf("C'est à dire le processus qui execute la commande \"ps -l\"\n", wait(NULL));
	}
	return EXIT_SUCCESS;
}