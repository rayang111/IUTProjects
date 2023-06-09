#include <unistd.h> 
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	
	pid_t fils_pid ; 
	
	fils_pid = fork ();

	if ( fils_pid == 0) {
		printf("Je suis le fils avec pid %d\n",getpid()); exit(3);
	} else {
		if (fils_pid > 0) {
			printf ("Je suis le pere avec pid %d.\n" , getpid ()); 
			printf("J’attends que mon fils se termine\n");
			wait (NULL) ;
			printf("Normalement mon fils en a fini!\n");
		} else {
			printf("Erreur dans la creation du fils\n");
		}
	}
	exit (0);
}