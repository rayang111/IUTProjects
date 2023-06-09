#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
	int i = 0;
	char* envstr = getenv("RUN_0");
	while(envstr != NULL) {
		printf("%s", envstr);
		i++;
		envstr = getenv("RUN_"+ (i+30));
	}
	return EXIT_SUCCESS;
}