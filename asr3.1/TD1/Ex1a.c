#include <stdlib.h>
#include <stdio.h>

void Afficher(int size, int* mat) {
	int i;
	printf("\nVoici votre matrice :\n");
	for(i = 0; i<size*size;i++) {
		if (i%size==0) {
			printf("\n");
		}
		printf("%3d", mat[i]);
	}
}

void MultiplicationScalaire(int size, int* mat) {
	int i;
	int sc;
	printf("\nChoisissez un nombre pour multiplier la matrice : ");
	scanf("%d", &sc);
	for (i = 0; i<(size*size); i++) {
		mat[i] = mat[i]*sc;
	}
}

void Addition(int size, int* mat) {
	int i;
	printf("\nCreer la 2éme matrice pour l'addition : \n");
	int* mat2 = malloc((size*size)*sizeof(int));
	for(i = 0; i<(size*size); i++) {
		scanf("%d", &mat2[i]);
	}
	for (i = 0; i<(size*size); i++) {
		mat[i] = mat[i]+mat2[i];
	}
	free(mat2);
}

void Multiplication(int size, int* mat) {
	int i;
}