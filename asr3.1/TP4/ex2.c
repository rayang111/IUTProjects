#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>

static void work_finished(int sig);


static void save(int sig); 


static void save_confirm(int sig);

pid_t fils;

int main(int argc, char const *argv[]) {
	int mode = 'a'; // ou 'b'   si a alors le fils n'a pas le temps de terminer
							//  si non a alors le fils termine son travail

	if(!(fils=fork())) { // Fils
		signal(SIGUSR2, &save);
		printf("Travail en cours");
		sleep(5);
		if (mode != 'a') {
			kill(getppid(), SIGQUIT); // Dire au père que le travail est terminé
		}
		
		pause();// En attente d'une réponse (après l'envoi de la fin du travail)
		pause();// En attente d'une réponse (après l'envoi de la confirmation de sauvegarde)
	} else {     // Père
		signal(SIGQUIT, &work_finished);
		signal(SIGINT, &save_confirm);
		if (mode == 'a') {
			sleep(2);
			printf("Dire au fils de sauvegarder")
		} else {
			pause(); // En attente de la fin du travail du fils
		}
		pause(); // En attente de la fin de la sauvegarde du fils
	}
	
	return EXIT_SUCCESS;
}

void work_finished(int sig) { // SIGQUIT
	printf("Le travail est terminé\n");
	kill(fils, SIGUSR2); // Dire au fils de sauvegarder
}

void save(int sig) { // SIGUSR2
	printf("Sauvegarde des données en cours...\n");
	sleep(1);
	kill(getppid(), SIGINT); // Dire au père que la sauvegarde est terminée

} 

void save_confirm(int sig) { // SIGINT
	printf("Sauvegarde terminée\n");
	sleep(.5);
	kill(fils, SIGKILL); // Kill du fils
} 