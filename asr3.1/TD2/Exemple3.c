#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>


void fils(int i); 

int main() {
	int status ;
	pid_t pid;
	
	pid = fork();
	
	if (pid == -1) perror("fork");
	else if (pid ==0) // creation du second fils 
			fils (1) ;
	
	pid = fork();
		
	if (pid == -1) perror("fork");
	else if (pid ==0) // creation du second fils 
		fils (2) ;
		
		
	if (wait(&status) > 0)
		printf("fin du fils %d\n", WEXITSTATUS(status));
	else perror("wait");
	
	if (wait(&status) > 0)
		printf("fin du fils %d\n", WEXITSTATUS(status));
	else perror("wait");
		
		
	if (wait(&status) > 0)
		printf("fin du fils %d\n", WEXITSTATUS(status));
	else perror("wait");
	
	return 0 ;
}

void fils (int i) {
	sleep(2);
	exit(i);
}