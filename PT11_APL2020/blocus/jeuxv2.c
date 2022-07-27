#include<stdio.h>
#include<stdlib.h>
#include<graph.h>

typedef struct position{
	int xmin;
	int xmax;
	int ymin;
	int ymax;
	int remplissagepossible;
} position;

void graphique(int nbtaille,couleur a, couleur b, int x, int y, int carre){
	int i;
	int j;
	for(i=0;i<nbtaille;i++){
		x=(800-(nbtaille*carre))/2;
		for(j=0;j<nbtaille;j++){
			ChoisirCouleurDessin(a);
			RemplirRectangle(x,y,carre,carre);
			ChoisirCouleurDessin(b);
			DessinerRectangle(x,y,carre,carre);
			x=x+40;
		}
		y=y+40;
	}
}

void remplissagetab(int nbtaille, position tableau[nbtaille][nbtaille],int carre, int x,int y){
	int i;
	int j;
	for(i=0;i<nbtaille;i++){
		x=(800-(nbtaille*carre))/2;
		for(j=0;j<nbtaille;j++){
			tableau[i][j].xmin=x;
			tableau[i][j].xmax=x+carre;
			tableau[i][j].ymin=y;
			tableau[i][j].ymax=y+carre;
			tableau[i][j].remplissagepossible=1;
		}
	}
}
void placerpion(int nbtaille,position tableau[nbtaille][nbtaille],int carre, int* posx, int* posy,couleur a,couleur b){
	int rempli=0;
	int i,j;
	while(rempli!=1){
		if(SourisCliquee()){
			for(i=0;i<nbtaille;i++){
				for(j=0;j<nbtaille;j++){
					if((tableau[i][j].xmin<=_X) && (tableau[i][j].xmax>=_X) && (tableau[i][j].ymin<=_Y) && (tableau[i][j].ymax>=_Y) && (tableau[i][j].remplissagepossible==1)){
						ChoisirCouleurDessin(a);
						RemplirRectangle(tableau[i][j].xmin,tableau[i][j].ymin,carre,carre);
						ChoisirCouleurDessin(b);
						DessinerRectangle(tableau[i][j].xmin,tableau[i][j].ymin,carre,carre);
						*posx=i;
						*posy=j;
						tableau[i][j].remplissagepossible=0;
						rempli=1;
					}
				}
			}

		}
	}
}



int main(){
	int nbtaille=3;
	position tableau[nbtaille][nbtaille];
	int carre=40;
	int i,j;
	int x;
	int y=(800-(nbtaille*carre))/2;
	int junperdu=0;
	int jdeuxperdu=0;
	int posxjun,posyjun,posxjdeux,posyjdeux;
	couleur blanc;
	couleur noir;
	couleur bleu;
	couleur rouge;

	InitialiserGraphique();
	CreerFenetre(10,10,800,800);

	blanc=CouleurParNom("blanc");
	blanc=CouleurParComposante(255,255,255);
	noir=CouleurParNom("noir");
	noir=CouleurParComposante(0,0,0);
	bleu=CouleurParNom("bleu");
	bleu=CouleurParComposante(0,0,255);
	rouge=CouleurParNom("rouge");
	rouge=CouleurParComposante(255,0,0);




	
	ChargerImageFond("fond.png");
	graphique(nbtaille,blanc,noir,x,y,carre);
	placerpion(nbtaille,tableau,carre, &posxjun, &posyjun,bleu,noir);
	placerpion(nbtaille,tableau,carre, &posxjdeux, &posyjdeux,rouge,noir);
	placerpion(nbtaille,tableau,carre, &posxjun, &posyjun,bleu,noir);
	placerpion(nbtaille,tableau,carre, &posxjdeux, &posyjdeux,rouge,noir);

	while(junperdu==0 && jdeuxperdu==0){

	}

	/*
	for(i=0;i<nbtaille;i++){
		x=(800-(nbtaille*carre))/2;
		for(j=0;j<nbtaille;j++){
			tableau[i][j].xmin=x;
			tableau[i][j].xmax=x+carre;
			tableau[i][j].ymin=y;
			tableau[i][j].ymax=y+carre;
			tableau[i][j].remplissagepossible=1;
			ChoisirCouleurDessin(noir);
			DessinerRectangle(x,y,carre,carre);
			x=x+40;
		}
		y=y+40;
	}
	while(rempli!=1){
		if(SourisCliquee()){
			for(i=0;i<nbtaille;i++){
				for(j=0;j<nbtaille;j++){
					if((tableau[i][j].xmin<=_X) && (tableau[i][j].xmax>=_X) && (tableau[i][j].ymin<=_Y) && (tableau[i][j].ymax>=_Y) && (tableau[i][j].remplissagepossible==1)){
						RemplirRectangle(tableau[i][j].xmin,tableau[i][j].ymin,carre,carre);
						rempli=1;
					}
				}
			}

		}
	}
	*/

	

    

	Touche();
    FermerGraphique();


return EXIT_SUCCESS;
}

