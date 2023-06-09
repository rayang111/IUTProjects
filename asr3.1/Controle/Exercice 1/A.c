#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	char* arg[3] = {"B1", "1", NULL};
	if (!fork()) {
		execvp("B1", arg);
	} else {
		if (!fork()) {
			arg[1] = "2";
			execvp("B1", arg);
		}
	}
	sleep(5);
	return EXIT_SUCCESS;
}