#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#include<time.h>
#include"menu.h"
#include"jeu.h"



int main(int argc, char * argv[]){

	/*INITIALISATION DES VARIABLES POUR LE MENU PRINCIPAL DU JEU*/
	taille nbcase[7];/*tableau qui contient les coordonnés et les valeurs des cases qui définissent la taille de la grille*/
	int poscase=10;/*position dans le tableau nbcase ou le joueur a cliqué*/
	taille nbj[2];/*tableau qui contient les coordonnés et les valeurs des cases qui définissent le nombre de joueur*/
	int posj=10;/*position dans le tableau nbj ou le joueur a cliqué*/
	taille jouer;/*contient les coordonnés du bouton jouer*/
	char* a="3";/*grille 3*3*/
	char* b="4";/*grille 4*4*/
	char* c="5";/*grille 5*5*/
	char* d="6";/*grille 6*6*/
	char* e="7";/*grille 7*7*/
	char* f="8";/*grille 8*8*/
	char* g="9";/*grille 9*9*/
	char* taille="Selectionner la taille :";
	char* njoueur="Nombre de joueur :";
	char* unj="1 joueur";
	char* deuxj="2 joueurs";
	char* chaine_jouer="Jouer !";
	int longeurchaine;/*permet de mesurer la longueur de la chaine pour la centrer*/
	couleur blanc;
	couleur bleu;
	couleur noir;
	couleur violet;
	couleur rouge;
	int nbjoueur=1;/*nombre de joueur*/
	int nbtaille=5;/*taille de la grille*/
	int play=0;/*indique si le joeur a cliqué sur jouer*/
	char* junplacerpion="Au joueur un de placer le pion";
	char* jdeuxplacerpion="Au joueur deux de placer le pion";
	char* jundeplacerpion="Au joueur un de deplacer le pion";
	char* jdeuxdeplacerpion="Au joueur deux de deplacer le pion";
	char* juncomdanecase="Au joueur un de condamner une case";
	char* jdeuxcomdanecase="Au joueur deux de condamner une case";
	int carre=40;/*taille carré dans la grille*/
	int i,j;
	int x;/*position x dans le graphique*/
	int y=(800-(nbtaille*carre))/2;/*position y dans le graphique*/
	int junperdu=0;/*prend en compte si le joueur 1 a perdu*/
	int jdeuxperdu=0;/*prend en compte si le joueur 2 a perdu*/
	int posxjun=1000;/*prend les position x dans le tableau occuper par le joueur 1 */
	int posxjdeux=1000;/*prend les position x dans le tableau occuper par le joueur 2*/
	int posyjun,posyjdeux;/*prend les position y dans le tableau occuper par le joueur 1 et 2*/
	int qter = 0;/*indique si le joeur a cliqué sur quitter*/
	int rj=0;/*indique si le joeur a cliqué sur rejouer*/
	char* ext="Quitter";
	char* rejouer="Rejouer";

	srand(time(NULL));
	InitialiserGraphique();
	CreerFenetre(10,10,800,800);



	/*----------------------CREATION DU MENU----------------------*/

	InitialiserGraphique();
	CreerFenetre(10,10,800,800);

    /*Creation des couleurs*/

	blanc=CouleurParNom("blanc");
	bleu=CouleurParNom("bleu");
	noir=CouleurParNom("noir");
	violet=CouleurParNom("violet");
	rouge=CouleurParNom("rouge");
	rouge=CouleurParComposante(255,0,0);
	blanc=CouleurParComposante(255,255,255);
	bleu=CouleurParComposante(0,0,255);
	noir=CouleurParComposante(0,0,0);
	violet=CouleurParComposante(127, 0, 255);

	ChoisirCouleurDessin(blanc);

	ChargerImageFond("fond.png");/*charge le fond*/

	x=290;

/* creer les cases qui définissent la taille de la grille*/
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
		nbcase[i].xmin=x;		/*rempli le tableau avec les coordonnés des cases qui permettent de choisir la taille*/
		nbcase[i].xmax=x+42;
		nbcase[i].ymin=y;
		nbcase[i].ymax=y+42;
		nbcase[i].remplissagepossible=1;
		nbcase[i].valeur=i+3;
		x=x+50;	
	}
	/*écrit le text qui permet de désigner a quoi servent les cases*/
	ChoisirCouleurDessin(noir);
	EcrireTexte(227,292,taille,1);
	EcrireTexte(292,392,njoueur,1);
	ChoisirCouleurDessin(blanc);
	EcrireTexte(225,290,taille,1);
	EcrireTexte(290,390,njoueur,1);

	ChoisirCouleurDessin(blanc);
	EcrireTexte(245,y+71,a,1);
	EcrireTexte(295,y+71,b,1);
	EcrireTexte(345,y+71,c,1);
	EcrireTexte(395,y+71,d,1);
	EcrireTexte(445,y+71,e,1);
	EcrireTexte(495,y+71,f,1);
	EcrireTexte(545,y+71,g,1);

	x=290;
	/*creer les cases qui définissent le nombre de joueur*/
	for(i=0;i<2;i++){

		ChoisirCouleurDessin(noir);
		RemplirRectangle(x+5,y+105,90,42);
		ChoisirCouleurDessin(blanc);
		ChoisirCouleurDessin(violet);
		RemplirRectangle(x,y+100,90,42);
		nbj[i].xmin=x;
		nbj[i].xmax=x+90;
		nbj[i].ymin=y+100;
		nbj[i].ymax=y+142;
		nbj[i].remplissagepossible=1;
		nbj[i].valeur=i+1;
		ChoisirCouleurDessin(blanc);
		x=x+110;
	}

	longeurchaine=TailleChaineEcran(unj,1);
	EcrireTexte(290+((90-longeurchaine)/2),y+175,unj,1);
	longeurchaine=TailleChaineEcran(deuxj,1);
	EcrireTexte(400+((90-longeurchaine)/2),y+175,deuxj,1);

	ChoisirCouleurDessin(noir);
	RemplirRectangle(355,605,90,42);
	ChoisirCouleurDessin(violet);
	RemplirRectangle(350,600,90,42);
	jouer.xmin=350;	/*jouer prend les coordonnés du bouton jouer */
	jouer.xmax=440;
	jouer.ymin=600;
	jouer.ymax=642;
	jouer.remplissagepossible=1;
	jouer.valeur=0;
	ChoisirCouleurDessin(blanc);
	longeurchaine=TailleChaineEcran(chaine_jouer, 1);
	EcrireTexte(350+((90-longeurchaine)/2),625,chaine_jouer,1);

    	/*CREATION DE LA BOUCLE PRINCIAPLE DU MENU*/
/* tant que le joueur na pas selectionné la taille de la grille et le nombre de joueur le bouton play ne fonctionnera pas*/
	/* et renvoi le nombre de joueur et la taille de la grille sélectionné*/
	while(play==0 || poscase==10 || posj==10){
		play=choisir(nbcase,nbj,jouer,&poscase,&posj,play,blanc,violet);

		if(poscase!=10){
			nbtaille=nbcase[poscase].valeur;
		}
		if(posj!=10){
			nbjoueur=nbj[posj].valeur;
		}

	}
	/*----------------------jeu----------------------*/

	while(qter==0){
		rj=0;
		junperdu=0;
		jdeuxperdu=0;
		posxjun=1000;
		posxjdeux=1000;
		poscase=10;
		posj=10;
		FermerGraphique();
		InitialiserGraphique();
		CreerFenetre(10,10,800,800);
		ChargerImageFond("fond.png");
		y=(800-(nbtaille*carre))/2;
		graphique(nbtaille,blanc,noir,x,y,carre);/* creer la grille centré avec des carré qui ont toujours la même taille */
		position tableau[nbtaille][nbtaille];
		for(i=0;i<nbtaille;i++){
			x=(800-(nbtaille*carre))/2;
			for(j=0;j<nbtaille;j++){ /*le tableau prend les coordonnés des cases de la grille et initialise leur remplissage possible*/
				tableau[i][j].xmin=x;
				tableau[i][j].xmax=x+carre;
				tableau[i][j].ymin=y;
				tableau[i][j].ymax=y+carre;
				tableau[i][j].remplissagepossible=1;
				x=x+40;
			}
			y=y+40;
		}

		if(nbjoueur==1){/*entre dans le if si il y a qu'un seul joueur*/
			placerpion(nbtaille,tableau,carre, &posxjun, &posyjun,bleu,noir,junplacerpion);/*tant que le joueur ne clique pas sur sur une case de la grille la fonction test si le joueur clique sur une case*/
			/*une fois que le joueur a cliqué sur la case la fontion remplie cette case de la couleur voulu*/
			botplacerpion(nbtaille,tableau,carre, &posxjdeux, &posyjdeux,rouge,noir);/*génere deux nombres aléatoires et parcours la grille pour placer le pion*/  
			while(junperdu==0 && jdeuxperdu==0){
				if(posxjun!=1000){
					junperdu=joueurperdu(nbtaille,tableau,carre, &posxjun, &posyjun);/*test si les cases autour de la case où se situe le joueur sont occupés si la fontion renvoie 1*/
				}
				if(junperdu==0){
					deplacerpion(nbtaille,tableau,carre, &posxjun, &posyjun,bleu,noir,blanc,jundeplacerpion);/* une fois que le joueur a cliqué sur une case libre adjacente a sa case cette case est 
					occuper par le joueur et son ancienne case est libéré*/ 
					condamneecase(nbtaille,tableau,carre,noir,noir,juncomdanecase,bleu);/*condamne une case libre*/
				}
				if(posxjun!=1000){
					junperdu=joueurperdu(nbtaille,tableau,carre, &posxjun, &posyjun);
				}
				if(posxjdeux!=1000 && junperdu==0){
					jdeuxperdu=joueurperdu(nbtaille,tableau,carre, &posxjdeux, &posyjdeux);
				}
				if(jdeuxperdu==0 && junperdu==0){
					botdeplacerpion(nbtaille,tableau,carre, &posxjdeux, &posyjdeux,rouge,noir,blanc);/*deplace aléatoirement le joueur a une case adjacente*/
					botcondamneecase(nbtaille,tableau,carre,noir,noir);/*condamne une case libre aléatoirement sur la grille*/
				}
				if(posxjdeux!=1000 && junperdu==0){
					jdeuxperdu=joueurperdu(nbtaille,tableau,carre, &posxjdeux, &posyjdeux);
				}
			}
		}

		if(nbjoueur==2){/*entre dans le if si il y a deux joueurs*/
			placerpion(nbtaille,tableau,carre, &posxjun, &posyjun,bleu,noir,junplacerpion);
			placerpion(nbtaille,tableau,carre, &posxjdeux, &posyjdeux,rouge,noir,jdeuxplacerpion);
			while(junperdu==0 && jdeuxperdu==0){
				if(posxjun!=1000){
					junperdu=joueurperdu(nbtaille,tableau,carre, &posxjun, &posyjun);
				}
				if(junperdu==0){
					deplacerpion(nbtaille,tableau,carre, &posxjun, &posyjun,bleu,noir,blanc,jundeplacerpion);
					condamneecase(nbtaille,tableau,carre,noir,noir,juncomdanecase,bleu);
				}
				if(posxjun!=1000){
					junperdu=joueurperdu(nbtaille,tableau,carre, &posxjun, &posyjun);
				}
				if(posxjdeux!=1000 && junperdu==0){
					jdeuxperdu=joueurperdu(nbtaille,tableau,carre, &posxjdeux, &posyjdeux);
				}
				if(jdeuxperdu==0 && junperdu==0){
					deplacerpion(nbtaille,tableau,carre, &posxjdeux, &posyjdeux,rouge,noir,blanc,jdeuxdeplacerpion);
					condamneecase(nbtaille,tableau,carre,noir,noir,jdeuxcomdanecase,rouge);
				}
				if(posxjdeux!=1000 && junperdu==0){
					jdeuxperdu=joueurperdu(nbtaille,tableau,carre, &posxjdeux, &posyjdeux);
				}
			}
		}
		/*----------------------menu de fin ----------------------*/

		if(junperdu == 0){
			FermerGraphique();
			InitialiserGraphique();
			CreerFenetre(10,10,800,800);
			ChargerImageFond("victoire_bleu.png");/*charge l'image de la victoire du joueur 1*/
		} else if(jdeuxperdu == 0){
			FermerGraphique();
			InitialiserGraphique();
			CreerFenetre(10,10,800,800);
			ChargerImageFond("victoire_rouge.png");/*charge l'image de la victoire du joueur 2*/
		}
		x=290;
		y=600;
		for(i=0;i<2;i++){/*creer les boutons rejouer et quitter*/

			ChoisirCouleurDessin(noir);
			RemplirRectangle(x+5,y+105,90,42);
			ChoisirCouleurDessin(blanc);
			ChoisirCouleurDessin(violet);
			RemplirRectangle(x,y+100,90,42);
			x=x+110;
		}
		ChoisirCouleurDessin(blanc);
		longeurchaine=TailleChaineEcran(rejouer,1);
		EcrireTexte(290+((90-longeurchaine)/2),y+125,rejouer,1);
		longeurchaine=TailleChaineEcran(ext,1);
		EcrireTexte(400+((90-longeurchaine)/2),y+125,ext,1);
		while(qter == 0 && rj ==0){/*test si on rejoue ou on quitte*/
			if(SourisCliquee()){
				if((290<=_X) && (380>=_X) && (700<=_Y) && (742>=_Y)){
					rj=1;
				}
				if((400<=_X) && (490>=_X) && (700<=_Y) && (742>=_Y)){
					qter=1;
				}

			}
		}
	}/*retourne au jeu si on appui sur le bouton rejouer*/
FermerGraphique();
return EXIT_SUCCESS;
}




