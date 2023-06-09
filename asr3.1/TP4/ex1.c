#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>

static void msg1(int sig);

int main(int argc, char const *argv[]) {
	pid_t fils;

	if(!(fils=fork())) {
		signal(SIGQUIT, &msg1);
		signal(SIGINT, &msg1);
		pause();
		pause();
		pause();
	} else {
		sleep(1);
		kill(fils, SIGQUIT);
		kill(fils, SIGINT);
		sleep(1);
		kill(fils, SIGKILL);
	}
	
	return EXIT_SUCCESS;
}

void msg1(int sig) {
	printf("JE TRAITE PAS\n");
} 