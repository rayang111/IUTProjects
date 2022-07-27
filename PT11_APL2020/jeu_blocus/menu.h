#ifndef MENU_H
#define MENU_H
typedef struct taille{
	int xmin;
	int xmax;
	int ymin;
	int ymax;
	int remplissagepossible;
	int valeur;
} taille;
int choisir(taille tableau[],taille tab[],taille jouer, int* pos,int *posd, int play,couleur a,couleur b);
#endif /* MENU_H */