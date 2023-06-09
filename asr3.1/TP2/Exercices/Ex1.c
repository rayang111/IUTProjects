#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
  int fluxe, fluxs, readchar;
  char caractere;
  fluxe = open("test.txt", O_RDONLY);
  fluxs = open("test2.txt", O_WRONLY | O_CREAT, 0600);
  pid_t pid;
  for (int i = 0; i<10;i++) {
    if (fluxe) {
    readchar = read(fluxe, &caractere, sizeof(char));

    }

    if (fluxs) {
        write(fluxs, &caractere, sizeof(char));

    }
  }
  
    pid = fork();
    if (pid == 0) {
        while(readchar != 0) {
           if (fluxe) {
            readchar = read(fluxe, &caractere, sizeof(char));
            
        }

        if (fluxs && readchar != 0) {
            write(fluxs, &caractere, sizeof(char)); 
        }
    }
        close(fluxe);
        close(fluxs);
        
    }
    return EXIT_SUCCESS;
}