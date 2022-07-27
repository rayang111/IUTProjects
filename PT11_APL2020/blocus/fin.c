#include<stdlib.h>
#include<stdio.h>
#include<graph.h>
#include"parametres.h"

int main(int argc, char const *argv[])
{
	InitialiserGraphique();
    CreerFenetre(10,10,800,800);

    int quitter = 0;
    couleur blanc;
	couleur bleu;
	couleur noir;
	couleur violet;
	char* joueur1_gagne="Joueur 1 gagne !";
	char* joueur2_gagne="Joueur 2 gagne !";
	int gagnant = 2;

    blanc=CouleurParNom("blanc");
    bleu=CouleurParNom("bleu");
    noir=CouleurParNom("noir");
    violet=CouleurParNom("violet");
	blanc=CouleurParComposante(255,255,255);
	bleu=CouleurParComposante(0,0,255);
	noir=CouleurParComposante(0,0,0);
	violet=CouleurParComposante(127, 0, 255);

	ChoisirCouleurDessin(blanc);

	ChargerImageFond("fond.png");

	if(gagnant == 1){
		ChargerImage("victoire_bleu.png", 0, 0, 0, 0, 800, 800);
	} else if(gagnant == 2){
		ChargerImage("victoire_rouge.png", 0, 0, 0, 0, 800, 800);
	}

	ChoisirCouleurDessin(noir);
	RemplirRectangle(360,610,200,42);
	ChoisirCouleurDessin(blanc);
	DessinerRectangle(349,599,202,44);
	ChoisirCouleurDessin(violet);
    RemplirRectangle(350,600,200,42);
    ChoisirCouleurDessin(blanc);
    EcrireTexte(420,627,"Quitter",1);

	while(quitter == 0){
		if(SourisCliquee()){
			if(_X >= 350 && _X <= 550 && _Y >= 600 && _Y <= 642){
				FermerGraphique();
				quitter == 1;
			}
		}
	}

	return EXIT_SUCCESS;
}