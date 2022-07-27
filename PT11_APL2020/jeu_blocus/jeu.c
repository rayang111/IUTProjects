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

void graphique(int nbtaille, couleur a, couleur b, int x, int y, int carre){
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
	RemplirRectangle(58,650,684,60);
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
void placerpion(int nbtaille,position tableau[nbtaille][nbtaille],int carre, int* posx, int* posy,couleur a,couleur b,char* txt){
	int rempli=0;
	int i,j;
	while(rempli!=1){
		ChoisirCouleurDessin(a);
		EcrireTexte(((800-(9*carre))/2)+30,680,txt,1);
		if(SourisCliquee()){
			for(i=0;i<nbtaille;i++){
				for(j=0;j<nbtaille;j++){
					if((tableau[i][j].xmin<_X) && (tableau[i][j].xmax>_X) && (tableau[i][j].ymin<_Y) && (tableau[i][j].ymax>_Y) && (tableau[i][j].remplissagepossible==1)){
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
	RemplirRectangle(58,650,684,60);
}

void botplacerpion(int nbtaille,position tableau[nbtaille][nbtaille],int carre, int* posx, int* posy,couleur a,couleur b){
	int rempli=0;
	int i,j;
	while(rempli!=1){
		i=rand()%(nbtaille+1);
		j=rand()%(nbtaille+1);
				if((tableau[i][j].remplissagepossible==1)){
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
	



void deplacerpion(int nbtaille,position tableau[nbtaille][nbtaille],int carre, int* posx, int* posy,couleur a,couleur b,couleur c,char* txt){
	int rempli=0;
	int i,j;
	while(rempli!=1){
		ChoisirCouleurDessin(a);
		EcrireTexte(((800-(9*carre))/2)+30,680,txt,1);
		if(SourisCliquee()){
			for(i=0;i<nbtaille;i++){
				for(j=0;j<nbtaille;j++){
					if((tableau[i][j].xmin<_X) && (tableau[i][j].xmax>_X) && (tableau[i][j].ymin<_Y) && (tableau[i][j].ymax>_Y) && (tableau[i][j].remplissagepossible==1) && !(*posx==i && *posy==j)){
						if((i==(*posx-1))||(i==(*posx))||(i==(*posx+1))){
							if((j==(*posy-1))||(j==(*posy))||(j==(*posy+1))){
								ChoisirCouleurDessin(a);
								RemplirRectangle(tableau[i][j].xmin,tableau[i][j].ymin,carre,carre);
								ChoisirCouleurDessin(b);
								DessinerRectangle(tableau[i][j].xmin,tableau[i][j].ymin,carre,carre);
								tableau[i][j].remplissagepossible=0;
								tableau[*posx][*posy].remplissagepossible=1;
								ChoisirCouleurDessin(c);
								RemplirRectangle(tableau[*posx][*posy].xmin,tableau[*posx][*posy].ymin,carre,carre);
								ChoisirCouleurDessin(b);
								DessinerRectangle(tableau[*posx][*posy].xmin,tableau[*posx][*posy].ymin,carre,carre);
								*posx=i;
								*posy=j;
								rempli=1;
							}
						}
					}
				}
			}

		}
	}
	RemplirRectangle(58,650,684,60);
}

void botdeplacerpion(int nbtaille,position tableau[nbtaille][nbtaille],int carre, int* posx, int* posy,couleur a,couleur b,couleur c){
	int rempli=0;
	int i,j;
	while(rempli!=1){
		i=rand()%(nbtaille+1);
		j=rand()%(nbtaille+1);
		if((tableau[i][j].remplissagepossible==1) && !(*posx==i && *posy==j)){
			if((i==(*posx-1))||(i==(*posx))||(i==(*posx+1 && *posx+1>*posx))){
				if((j==(*posy-1))||(j==(*posy))||(j==(*posy+1 && *posy+1>*posy))){
					ChoisirCouleurDessin(a);
					RemplirRectangle(tableau[i][j].xmin,tableau[i][j].ymin,carre,carre);
					ChoisirCouleurDessin(b);
					DessinerRectangle(tableau[i][j].xmin,tableau[i][j].ymin,carre,carre);
					tableau[i][j].remplissagepossible=0;
					tableau[*posx][*posy].remplissagepossible=1;
					ChoisirCouleurDessin(c);
					RemplirRectangle(tableau[*posx][*posy].xmin,tableau[*posx][*posy].ymin,carre,carre);
					ChoisirCouleurDessin(b);
					DessinerRectangle(tableau[*posx][*posy].xmin,tableau[*posx][*posy].ymin,carre,carre);
					*posx=i;
					*posy=j;
					rempli=1;
				}
			}
		}
	}
}



int joueurperdu(int nbtaille,position tableau[nbtaille][nbtaille],int carre, int* posx, int* posy){
	int i,j;
	int perdu=1;
	for(i=0;i<nbtaille;i++){
		for(j=0;j<nbtaille;j++){
			if(!(*posx==i && *posy==j)){
				if((i==(*posx-1))||(i==(*posx))||(i==(*posx+1))){
					if((j==(*posy-1))||(j==(*posy))||(j==(*posy+1))){
						if(tableau[i][j].remplissagepossible==1){
							perdu=0;
						}
					}
				}
			}
		}
	}
	return perdu;
}

int condamneecase(int nbtaille,position tableau[nbtaille][nbtaille],int carre,couleur a,couleur b,char* txt,couleur c){
	int condamnee=0;
	int i,j;
	while(condamnee!=1){
		ChoisirCouleurDessin(c);
		EcrireTexte(((800-(9*carre))/2)+10,680,txt,1);
		if(SourisCliquee()){
			for(i=0;i<nbtaille;i++){
				for(j=0;j<nbtaille;j++){
					if((tableau[i][j].xmin<_X) && (tableau[i][j].xmax>_X) && (tableau[i][j].ymin<_Y) && (tableau[i][j].ymax>_Y) && (tableau[i][j].remplissagepossible==1)){
						ChoisirCouleurDessin(a);
						RemplirRectangle(tableau[i][j].xmin,tableau[i][j].ymin,carre,carre);
						ChoisirCouleurDessin(b);
						DessinerRectangle(tableau[i][j].xmin,tableau[i][j].ymin,carre,carre);
						tableau[i][j].remplissagepossible=0;
						condamnee=1;
					}
				}
			}

		}
	}
	RemplirRectangle(58,650,684,60);
}

int botcondamneecase(int nbtaille,position tableau[nbtaille][nbtaille],int carre,couleur a,couleur b){
	int condamnee=0;
	int i,j;
	while(condamnee!=1){
		i=rand()%(nbtaille+1);
		j=rand()%(nbtaille+1);
		if((tableau[i][j].remplissagepossible==1)){
			ChoisirCouleurDessin(a);
			RemplirRectangle(tableau[i][j].xmin,tableau[i][j].ymin,carre,carre);
			ChoisirCouleurDessin(b);
			DessinerRectangle(tableau[i][j].xmin,tableau[i][j].ymin,carre,carre);
			tableau[i][j].remplissagepossible=0;
			condamnee=1;
		}
	}
}
