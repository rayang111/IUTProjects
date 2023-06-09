#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int status;

    pid = fork();


    if (pid != 0) {
        printf("le pid du fils est %d\n", pid);
        waitpid(pid, &status, WUNTRACED);

        if (WIFSIGNALED(status)) {
            printf("tué par le signal %d\n", WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            printf("arrêté par le signal %d\n", WSTOPSIG(status));
        } 
    } else {
        while(1){}
    }

exit(EXIT_SUCCESS);

}