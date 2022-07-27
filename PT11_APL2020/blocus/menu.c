#include<stdlib.h>
#include<stdio.h>
#include<graph.h>



/*INSTRUCTIONS POUR LES COMMENTAIRES : 
	
	Si le commentaire est en MAJUSCULE, alors il signifie une partie principale du code.
	Si c'est en miniscule, alors c'est des sous parties des parties parincipales du code.
*/

int main(){

	/*INITIALISATION DES VARIABLES POUR LE MENU PRINCIPAL DU JEU*/

    char* taille="Selectionner la taille :";
    char* nbjoueur="Nombre de joueur :";
    char* unj="1 joueur";
    char* deuxj="2 joueurs";
    char* chaine_jouer="Jouer !";
    int longeurchaine;
	couleur blanc;
	couleur bleu;
	couleur noir;
	couleur violet;
	int i;
	int x=225;
	int y=400;
	int nb_joueurs = 0;
	int nb_resolution = 0;
    int play=0;
 
	/*CREATION DU MENU*/

    InitialiserGraphique();
    CreerFenetre(10,10,800,800);

    /*Creation des couleurs*/

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

	x=290;
    
    for(i=0;i<7;i++){

        ChoisirCouleurDessin(noir);
		RemplirRectangle(x-60,y+5,42,42);
        x=x+50;
    }

    ChoisirCouleurDessin(violet);
   	x=225;

    for(i=0;i<7;i++){
    	DessinerRectangle(x,y,42,42);
    	RemplirRectangle(x,y,42,42);
    	x=x+50;	

    }
    ChoisirCouleurDessin(noir);
    EcrireTexte(227,392,taille,1);
    EcrireTexte(292,492,nbjoueur,1);
    ChoisirCouleurDessin(blanc);
    EcrireTexte(225,390,taille,1);
    EcrireTexte(290,490,nbjoueur,1);

    EcrireTexte(245,y+21,"3",1);
    EcrireTexte(295,y+21,"4",1);
    EcrireTexte(345,y+21,"5",1);
    EcrireTexte(395,y+21,"6",1);
    EcrireTexte(445,y+21,"7",1);
    EcrireTexte(495,y+21,"8",1);
    EcrireTexte(545,y+21,"9",1);

    x=290;

    for(i=0;i<2;i++){

        ChoisirCouleurDessin(noir);
		RemplirRectangle(x+5,y+105,90,42);
		ChoisirCouleurDessin(blanc);
        ChoisirCouleurDessin(violet);
        RemplirRectangle(x,y+100,90,42);
        ChoisirCouleurDessin(blanc);
        x=x+110;
    }

    longeurchaine=TailleChaineEcran(unj,1);
    EcrireTexte(290+((90-longeurchaine)/2),y+125,unj,1);
    longeurchaine=TailleChaineEcran(deuxj,1);
    EcrireTexte(400+((90-longeurchaine)/2),y+125,deuxj,1);

    ChoisirCouleurDessin(noir);
	RemplirRectangle(355,605,90,42);
    ChoisirCouleurDessin(violet);
    RemplirRectangle(350,600,90,42);
    ChoisirCouleurDessin(blanc);
    longeurchaine=TailleChaineEcran(chaine_jouer, 1);
    EcrireTexte(350+((90-longeurchaine)/2),625,chaine_jouer,1);

    /*CREATION DE LA BOUCLE PRINCIAPLE DU MENU*/

	while(play==0)
	{
		if(SourisCliquee()){ /*Si l'utilisateur fait un clic*/
			SourisPosition();
			if (_X >= 255 && _Y >= 400 && _X <= 297 && _Y <= 442)  /*Si le bouton 3 a été choisi*/
			{
				ChoisirCouleurDessin(blanc);
				RemplirRectangle(255-30,400,42,42);
				ChoisirCouleurDessin(bleu);
				EcrireTexte(245,y+21,"3",1);
				ChoisirCouleurDessin(blanc);
				nb_resolution = 3;
			} else {
				ChoisirCouleurDessin(violet);
				RemplirRectangle(255-30,400,42,42);
				ChoisirCouleurDessin(blanc);
				EcrireTexte(245,y+21,"3",1);
			}
			if (_X >= 305 && _Y >= 400 && _X <= 347 && _Y <= 442) /*Si le bouton 4 a été choisi*/
			{
				ChoisirCouleurDessin(blanc);
				RemplirRectangle(305-30,400,42,42);
				ChoisirCouleurDessin(bleu);
				EcrireTexte(295,y+21,"4",1);
				ChoisirCouleurDessin(blanc);
				nb_resolution = 4;
			}else {
				ChoisirCouleurDessin(violet);
				RemplirRectangle(305-30,400,42,42);
				ChoisirCouleurDessin(blanc);
				EcrireTexte(295,y+21,"4",1);
			}
			if (_X >= 355 && _Y >= 400 && _X <= 389 && _Y <= 442) /*Si le bouton 5 a été choisi*/
			{
				ChoisirCouleurDessin(blanc);
				RemplirRectangle(355-30,400,42,42);
				ChoisirCouleurDessin(bleu);
				EcrireTexte(345,y+21,"5",1);
				ChoisirCouleurDessin(blanc);
				nb_resolution = 5;
			}else{
				ChoisirCouleurDessin(violet);
				RemplirRectangle(355-30,400,42,42);
				ChoisirCouleurDessin(blanc);
				EcrireTexte(345,y+21,"5",1);				
			}
			if (_X >= 405 && _Y >= 400 && _X <= 431 && _Y <= 442) /*Si le bouton 6 a été choisi*/
			{
				ChoisirCouleurDessin(blanc);
				RemplirRectangle(405-30,400,42,42);
				ChoisirCouleurDessin(bleu);
				EcrireTexte(395,y+21,"6",1);
				ChoisirCouleurDessin(blanc);
				nb_resolution = 6;
			}else{
				ChoisirCouleurDessin(violet);
				RemplirRectangle(405-30,400,42,42);
				ChoisirCouleurDessin(blanc);
				EcrireTexte(395,y+21,"6",1);				
			}
			if (_X >= 455 && _Y >= 400 && _X <= 473 && _Y <= 442) /*Si le bouton 7 a été choisi*/
			{
				ChoisirCouleurDessin(blanc);
				RemplirRectangle(455-30,400,42,42);
				ChoisirCouleurDessin(bleu);
				EcrireTexte(445,y+21,"7",1);
				ChoisirCouleurDessin(blanc);
				nb_resolution = 7;
			}else{
				ChoisirCouleurDessin(violet);
				RemplirRectangle(455-30,400,42,42);
				ChoisirCouleurDessin(blanc);
				EcrireTexte(445,y+21,"7",1);				
			}
			if (_X >= 505 && _Y >= 400 && _X <= 512 && _Y <= 442) /*Si le bouton 8 a été choisi*/
			{
				ChoisirCouleurDessin(blanc);
				RemplirRectangle(505-30,400,42,42);
				ChoisirCouleurDessin(bleu);
				EcrireTexte(495,y+21,"8",1);
				ChoisirCouleurDessin(blanc);
				nb_resolution = 8;
			}else{
				ChoisirCouleurDessin(violet);
				RemplirRectangle(505-30,400,42,42);
				ChoisirCouleurDessin(blanc);
				EcrireTexte(495,y+21,"8",1);				
			}
			if (_X >= 555 && _Y >= 400 && _X <= 557 && _Y <= 442) /*Si le bouton 9 a été choisi*/
			{
				ChoisirCouleurDessin(blanc);
				RemplirRectangle(555-30,400,42,42);
				ChoisirCouleurDessin(bleu);
				EcrireTexte(545,y+21,"9",1);
				ChoisirCouleurDessin(blanc);
				nb_resolution = 9;
			}else{
				ChoisirCouleurDessin(violet);
				RemplirRectangle(555-30,400,42,42);
				ChoisirCouleurDessin(blanc);
				EcrireTexte(545,y+21,"9",1);				
			}
			if (_X >= 290 && _Y >= 500 && _X <= 380 && _Y <= 542) /*Si le bouton Joueur 1 a été choisi*/
			{
				ChoisirCouleurDessin(blanc);
				RemplirRectangle(290,500,90,42);
				ChoisirCouleurDessin(bleu);
				longeurchaine=TailleChaineEcran(unj,1);
				EcrireTexte(290+((90-longeurchaine)/2),y+125,unj,1);
				ChoisirCouleurDessin(blanc);
				nb_joueurs = 1;
			}else{
				ChoisirCouleurDessin(violet);
				RemplirRectangle(290,500,90,42);
				ChoisirCouleurDessin(blanc);
				longeurchaine=TailleChaineEcran(unj,1);
				EcrireTexte(290+((90-longeurchaine)/2),y+125,unj,1);				
			}
			if (_X >= 400 && _Y >= 500 && _X <= 490 && _Y <= 542) /*Si le bouton Joueur 2 a été choisi*/
			{
				ChoisirCouleurDessin(blanc);
				RemplirRectangle(400,500,90,42);
				ChoisirCouleurDessin(bleu);
				longeurchaine=TailleChaineEcran(deuxj,1);
				EcrireTexte(400+((90-longeurchaine)/2),y+125,deuxj,1);
				ChoisirCouleurDessin(blanc);
				nb_joueurs = 2;
			}else{
				ChoisirCouleurDessin(violet);
				RemplirRectangle(400,500,90,42);
				ChoisirCouleurDessin(blanc);
				longeurchaine=TailleChaineEcran(deuxj,1);
				EcrireTexte(400+((90-longeurchaine)/2),y+125,deuxj,1);			
			}
			if (_X >= 350 && _Y >= 600 && _X <= 440 && _Y <= 642) /*Si le bouton Jouer a été choisi*/
			{
				ChoisirCouleurDessin(blanc);
				RemplirRectangle(350,600,90,42);
				ChoisirCouleurDessin(bleu);
				longeurchaine=TailleChaineEcran(chaine_jouer, 1);
				EcrireTexte(350+((90-longeurchaine)/2),625,chaine_jouer,1);
				ChoisirCouleurDessin(blanc);
				if(nb_joueurs > 0 && nb_resolution > 0){
					/*jeu(nb_joueurs, nb_resolution);*/
					play=1;
				}																
			}else{
					ChoisirCouleurDessin(violet);
					RemplirRectangle(350,600,90,42);
					ChoisirCouleurDessin(blanc);
					longeurchaine=TailleChaineEcran(chaine_jouer, 1);
					EcrireTexte(350+((90-longeurchaine)/2),625,chaine_jouer,1);
			}
		}
       
	}
     printf("%d,%d",nb_resolution,nb_joueurs);

    return EXIT_SUCCESS;
}