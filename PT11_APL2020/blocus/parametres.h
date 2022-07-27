#ifndef PARAMETRES_H
#define PARAMETRES_H

typedef struct jouer{
	int num_joueur;
	int score;
	int temps;
}jouer;

jouer jeu(int nb_joueur, int nb_resolution);

#endif /* PARAMETRES_H */