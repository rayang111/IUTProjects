#include <stdlib.h>
#include <stdio.h>
#include "Ex1a.h"



int main(int argc, char const *argv[]) {
	int size;
	int choix;
	int i;
	int menu = 1;
	printf("Rentrez la taille de la matrice : ");
	scanf("%d", &size);

	int* mat = malloc((size*size)*sizeof(int));
	for(i = 0; i<(size*size); i++) {
		scanf("%d", &mat[i]);
	}

	Afficher(size, mat);

	while (menu) {
		printf("\n\n1. Multiplication scalaire\n2. Addition\n3. Multiplication\n4. Quitter\n\nChoix : ");
		scanf("%d", &choix);
		if (choix == 4) {
			menu = 0;
		} else if (choix == 1) {
			MultiplicationScalaire(size, mat);
			Afficher(size, mat);

		} else if (choix == 2) {
			Addition(size, mat);
			Afficher(size, mat);

		} else if (choix == 3) {
			Multiplication(size, mat);
			Afficher(size, mat);
		}
	}
	
	

	free(mat);

	return EXIT_SUCCESS;
}