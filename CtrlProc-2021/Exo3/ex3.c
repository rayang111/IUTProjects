#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char const *argv[]) {
	int pnum[2];
	int pchar[2];
	int pnumretour[2];
	int pcharretour[2];
	pipe(pnum);
	pipe(pchar);
	pipe(pnumretour);
	pipe(pcharretour);
	int somme = 0;
	int occurences[26];

	int i;
	unsigned char c;

	///////////////////////////////////////////////

	if (!fork()) {  // Le fils qui gère les chiffres
		close(pcharretour[0]);
		close(pcharretour[1]);
		close(pnumretour[0]);
		close(pnum[1]);
		close(pchar[1]);
		close(pchar[0]);
		// Reception et traitement des informations
		while(read(pnum[0], &c, 1) > 0) {
			somme += ((int) c - 48);
		}
		// Envoi du résultat
		write(pnumretour[1], &somme, sizeof(int));
		close(pcharretour[1]);
		close(pchar[0]);
		return EXIT_SUCCESS;
	} 

	///////////////////////////////////////////////

	if (!fork()) {  // Le fils qui gère les lettres
		close(pcharretour[0]);
		close(pnumretour[0]);
		close(pnumretour[1]);
		close(pchar[1]);
		close(pnum[0]);
		close(pnum[1]);
		// Initialisation du tableau
		for(i = 0;i<26;i++) {
			occurences[i] = 0;
		}
		// Reception et traitement des informations
		while(read(pchar[0], &c, 1) > 0) {
			occurences[(int)c-65]++;
		}
		// Envoi du résultat
		for(i = 0; i<26; i++) {
			write(pcharretour[1], occurences+i, sizeof(int));
		}
		close(pcharretour[1]);
		close(pchar[0]);
		return EXIT_SUCCESS;
	}

	///////////////////////////////////////////////
	// Le père
	close(pnum[0]);
	close(pchar[0]);
	printf("Tapez '0' puis entrer pour terminer la saisie\n");

	// Reception de l'entrée standard et envoi aux fils
	while(((c=getchar())!='0')){
		if ((c>47) && (c<58)) {
			write(pnum[1], &c, 1);
		} else if ((c>40) && (c<91)) {
			write(pchar[1], &c, 1);
		} else if ((c>96) && (c<123)) {
			c-=32;
			write(pchar[1], &c, 1);
		}
	}
	close(pnum[1]);
	close(pchar[1]);

	// Reception du résultat du fils qui gere les chiffres
	read(pnumretour[0], &somme, sizeof(int));
	close(pnumretour[0]);

	// Reception du résultat du fils qui gere les lettres
	for(i = 0; i<26; i++) {
		read(pcharretour[0], occurences+i, sizeof(int));
	}
	close(pcharretour[0]);

	// Affichage du resultat
	printf("\nLa somme des chiffres est de %d\n\n", somme);
	for(i = 0; i<26; i++) {
		printf("%c : %d\n", (char) i+65 , occurences[i]);
	}
	return EXIT_SUCCESS;
}