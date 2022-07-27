#ifndef JEU_H
#define JEU_H

typedef struct position{
	int xmin;
	int xmax;
	int ymin;
	int ymax;
	int remplissagepossible;
} position;

void graphique(int nbtaille, couleur a, couleur b, int x, int y, int carre);
void remplissagetab(int nbtaille, position tableau[nbtaille][nbtaille],int carre, int x,int y);
void placerpion(int nbtaille,position tableau[nbtaille][nbtaille],int carre, int* posx, int* posy,couleur a,couleur b,char* txt);
void botplacerpion(int nbtaille,position tableau[nbtaille][nbtaille],int carre, int* posx, int* posy,couleur a,couleur b);
void deplacerpion(int nbtaille,position tableau[nbtaille][nbtaille],int carre, int* posx, int* posy,couleur a,couleur b,couleur c,char* txt);
void botdeplacerpion(int nbtaille,position tableau[nbtaille][nbtaille],int carre, int* posx, int* posy,couleur a,couleur b,couleur c);
int joueurperdu(int nbtaille,position tableau[nbtaille][nbtaille],int carre, int* posx, int* posy);
int condamneecase(int nbtaille,position tableau[nbtaille][nbtaille],int carre,couleur a,couleur b,char* txt,couleur c);
int botcondamneecase(int nbtaille,position tableau[nbtaille][nbtaille],int carre,couleur a,couleur b);


#endif /* JEU_H */