#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>

static void babouche() {
	printf("Je recois le signal 5/5");
}

int main(int argc, char const *argv[]) {
	pid_t pid;
	signal(SIGUSR2, &babouche);
	if (pid=fork()) { // PERE
		kill(pid, SIGUSR2);
	} else { // FILS
		pause();
	}
	return EXIT_SUCCESS;
}

// La réponse a la question : 
// "Est ce que le handler de signaux d'un processus est hérité par son fils?"
// Est non.