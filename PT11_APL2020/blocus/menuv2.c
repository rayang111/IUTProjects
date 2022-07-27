#include<stdlib.h>
#include<stdio.h>
#include<graph.h>

typedef struct taille{
	int xmin;
	int xmax;
	int ymin;
	int ymax;
	int remplissagepossible;
	int valeur;
} taille;

int choisir(taille tableau[],taille tab[],taille jouer, int* pos,int *posd, int play,couleur a,couleur b){
	int i,j;
	if(SourisCliquee()){
		for(i=0;i<=6;i++){
			if((tableau[i].xmin<=_X) && (tableau[i].xmax>=_X) && (tableau[i].ymin<=_Y) && (tableau[i].ymax>=_Y) && (tableau[i].remplissagepossible==1) && !(*pos==i)){
				ChoisirCouleurDessin(a);
				RemplirRectangle(tableau[i].xmin,tableau[i].ymin,42,42);
				tableau[i].remplissagepossible=0;
				tableau[*pos].remplissagepossible=1;
				ChoisirCouleurDessin(b);
				if(*pos!=10){		
					RemplirRectangle(tableau[*pos].xmin,tableau[*pos].ymin,42,42);
				}
				*pos=i;
			}
		}
		for(i=0;i<=2;i++){
			if((tab[i].xmin<=_X) && (tab[i].xmax>=_X) && (tab[i].ymin<=_Y) && (tab[i].ymax>=_Y) && (tab[i].remplissagepossible==1) && !(*posd==i)){
				ChoisirCouleurDessin(a);
				RemplirRectangle(tab[i].xmin,tab[i].ymin,90,42);
				tab[i].remplissagepossible=0;
				tab[*posd].remplissagepossible=1;
				ChoisirCouleurDessin(b);
				if(*posd!=10){		
					RemplirRectangle(tab[*posd].xmin,tab[*posd].ymin,90,42);
				}
				*posd=i;
			}
		}
		if((jouer.xmin<=_X) && (jouer.xmax>=_X) && (jouer.ymin<=_Y) && (jouer.ymax>=_Y)){
			return 1;
		}
	}
	return 0;	
}


/*INSTRUCTIONS POUR LES COMMENTAIRES : 
	
	Si le commentaire est en MAJUSCULE, alors il signifie une partie principale du code.
	Si c'est en miniscule, alors c'est des sous parties des parties parincipales du code.
*/

int main(){

	/*INITIALISATION DES VARIABLES POUR LE MENU PRINCIPAL DU JEU*/
	taille nbcase[7];
	int poscase=10;
	taille nbj[2];
	int posj=10;
	taille jouer;
	char* a="3";
	char* b="4";
	char* c="5";
	char* d="6";
	char* e="7";
	char* f="8";
	char* g="9";
    char* taille="Selectionner la taille :";
    char* njoueur="Nombre de joueur :";
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
	int nbjoueur=1;
	int nbtaille=5;
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
    	nbcase[i].xmin=x;
		nbcase[i].xmax=x+42;
		nbcase[i].ymin=y;
		nbcase[i].ymax=y+42;
		nbcase[i].remplissagepossible=1;
		nbcase[i].valeur=i+3;
    	x=x+50;	

    }
    ChoisirCouleurDessin(noir);
    EcrireTexte(227,392,taille,1);
    EcrireTexte(292,492,njoueur,1);
    ChoisirCouleurDessin(blanc);
    EcrireTexte(225,390,taille,1);
    EcrireTexte(290,490,njoueur,1);

    ChoisirCouleurDessin(noir);
    EcrireTexte(245,y+71,a,1);
    EcrireTexte(295,y+71,b,1);
    EcrireTexte(345,y+71,c,1);
    EcrireTexte(395,y+71,d,1);
    EcrireTexte(445,y+71,e,1);
    EcrireTexte(495,y+71,f,1);
    EcrireTexte(545,y+71,g,1);

    x=290;

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
    EcrireTexte(290+((90-longeurchaine)/2),y+125,unj,1);
    longeurchaine=TailleChaineEcran(deuxj,1);
    EcrireTexte(400+((90-longeurchaine)/2),y+125,deuxj,1);

    ChoisirCouleurDessin(noir);
	RemplirRectangle(355,605,90,42);
    ChoisirCouleurDessin(violet);
    RemplirRectangle(350,600,90,42);
    jouer.xmin=350;
	jouer.xmax=440;
	jouer.ymin=600;
	jouer.ymax=642;
	jouer.remplissagepossible=1;
	jouer.valeur=0;
    ChoisirCouleurDessin(blanc);
    longeurchaine=TailleChaineEcran(chaine_jouer, 1);
    EcrireTexte(350+((90-longeurchaine)/2),625,chaine_jouer,1);

    /*CREATION DE LA BOUCLE PRINCIAPLE DU MENU*/

	while(play==0){
		play=choisir(nbcase,nbj,jouer,&poscase,&posj,play,blanc,violet);

		if(poscase!=10){
			nbtaille=nbcase[poscase].valeur;
		}
		if(posj!=10){
			nbjoueur=nbj[posj].valeur;
		}
       
	}



 
}