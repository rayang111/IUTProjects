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

int main(){
	int nbtaille=3;
	position tableau[nbtaille][nbtaille];
	int carre=40;
	int i,j;
	int x;
	int y=(800-(nbtaille*carre))/2;
	int rempli=0;
	couleur blanc;
	couleur noir;

	InitialiserGraphique();
	CreerFenetre(10,10,800,800);

	blanc=CouleurParNom("blanc");
	blanc=CouleurParComposante(255,255,255);
	noir=CouleurParNom("noir");
	noir=CouleurParComposante(0,0,0);




	
	ChargerImageFond("fond.png");

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

	

    

	Touche();
    FermerGraphique();


return EXIT_SUCCESS;
}

