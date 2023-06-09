#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	char* arg[2] = {NULL, NULL};
	if (!fork()) {
		if (argv[1][0] == '1') {
			arg[0] = "C1";
		} else {
			arg[0] = "C2";
		}
		execvp(arg[0], arg);
	}
	sleep(5);
	return EXIT_SUCCESS;
}