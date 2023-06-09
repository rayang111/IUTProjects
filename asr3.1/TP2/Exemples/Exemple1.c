
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>

pid_t pid;               // pour récupérer le pid du nouveau processus 

int main() {

        switch(pid = fork()) { 
        case (pid_t) -1:     // l’appel de fork a échoué 
            perror("Création de processus"); 
            exit(2); 
        case (pid_t)0:      // ici, ça concerne le processus fils 
            printf("valeur de fork dans le fils = %d\n",pid); 
            printf("je suis le processus %d de père %d\n",getpid(), getppid()); 
            printf("fin du processus fils\n"); 
            exit(0); 
        default:                 // ici, c’est le processus père 
             printf("valeur de fork dans le père = %d\n",pid); 
            printf("je suis le processus %d de père %d\n",getpid(), getppid()); 
            printf("fin du processus père\n");
        }
        return EXIT_SUCCESS;
}
