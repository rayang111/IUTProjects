#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	write(1, "mammouth", 8);
	pid_t psid = fork();
	if (psid == 0) {
		write(1, "\nlapinou", 8);
	}
	return EXIT_SUCCESS;
}