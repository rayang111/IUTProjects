#include<stdio.h>
#include<stdlib.h>
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

