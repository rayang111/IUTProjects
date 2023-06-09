#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
	int pid, fp, i, j;
	char ch[4];
	
	fp = open("fichier", O_RDWR);
	pid = fork();
	
	if (pid == 0) {
		for (i = 0; i < 4; i++) {
			read(fp, ch, 4);
			printf("hello fils : %s\n", ch);
			sleep(4);
		}
	} else {
		for (j = 0; j < 3; j++) {
			read(fp, ch, 4);
			printf("Hello père : %s\n", ch);
			sleep(5);
		}
		wait(NULL);
		close(fp);
	}
	return 1;
}