#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 20

// Rayan GRIB
// La plupart du programme fonctionne sauf quelques fonctionnatlit�s. L'algorithme utilis� n'est pas parfait.
// Ce qui ne fonctionne pas c'est la d�tection en diagonale et le fait que lorqu'on remplie la premi�re colone, la derniere se remplie aussi. De m�me si on remplie la derni�re colonne colonne �a remplie la premi�re.
// Ceci est peut �tre d� � un probl�mes de tableaux.

void vider_buffer();
int detecter(char tableau[7][6]);
int placer(int colonne_choisie, char tableau[7][6], int joueur);
void afficher_tableau(char tableau[7][6]);
void jeu(char tableau_jeu[7][6]);
void debut(char tableau_jeu[7][6]);

// Fonction permtant de vider le buffer pour �viter le d�bordement de tableau pour les puesdos.
void vider_buffer(void)

{
    int caractere = 0;
    while (caractere != '\n' && caractere != EOF)
    {
        caractere = getchar();
    }
}

// Fonction permetant de d�tecter lorsque qu'il y a un gaganant
int detecter(char tableau[7][6])
{
    int nb = 0;
    int stop = 0;
    int stop_boucle = 0;
    int joueur_gagnant = 0;
    // Vertical R
    for (int case_x = 0; case_x < 6; case_x++)
    {
        stop = 0;
        for (int case_y = 0; case_y < 7; case_y++)
        {
            if (stop_boucle == 0)
            {
                if (tableau[case_y][case_x] == 'R' && stop == 0)
                {
                    nb = nb + 1;
                    if (nb == 4)
                    {
                        joueur_gagnant = 1;
                        stop_boucle = 1;
                    }
                }
                if (tableau[case_y][case_x] != 'R' && stop == 0)
                {
                    stop = 1;
                    nb = 0;
                }
                if (tableau[case_y][case_x] == 'R' && stop == 1)
                {
                    nb = nb + 1;
                    stop = 0;
                }
            }
        }
    }
    // Vertical J
    for (int case_x = 0; case_x < 6; case_x++)
    {
        stop = 0;
        for (int case_y = 0; case_y < 7; case_y++)
        {
            if (stop_boucle == 0)
            {
                if (tableau[case_y][case_x] == 'J' && stop == 0)
                {
                    nb = nb + 1;
                    if (nb == 4)
                    {
                        joueur_gagnant = 2;
                        stop_boucle = 1;
                    }
                }
                if (tableau[case_y][case_x] != 'J' && stop == 0)
                {
                    stop = 1;
                    nb = 0;
                }
                if (tableau[case_y][case_x] == 'J' && stop == 1)
                {
                    nb = nb + 1;
                    stop = 0;
                }
            }
        }
    }
    // Horizontal R
    for (int case_y = 0; case_y < 7; case_y++)
    {
        stop = 0;
        for (int case_x = 0; case_x < 6; case_x++)
        {
            if (stop_boucle == 0)
            {
                if (tableau[case_y][case_x] == 'R' && stop == 0)
                {
                    nb = nb + 1;
                    if (nb == 4)
                    {
                        joueur_gagnant = 1;
                        stop_boucle = 1;
                    }
                }
                if (tableau[case_y][case_x] != 'R' && stop == 0)
                {
                    stop = 1;
                    nb = 0;
                }
                if (tableau[case_y][case_x] == 'R' && stop == 1)
                {
                    nb = nb + 1;
                    stop = 0;
                }
            }
        }
    }
    // Horizontal J
    for (int case_y = 0; case_y < 7; case_y++)
    {
        stop = 0;
        for (int case_x = 0; case_x < 6; case_x++)
        {
            if (stop_boucle == 0)
            {
                if (tableau[case_y][case_x] == 'J' && stop == 0)
                {
                    nb = nb + 1;
                    if (nb == 4)
                    {
                        joueur_gagnant = 2;
                        stop_boucle = 1;
                    }
                }
                if (tableau[case_y][case_x] != 'J' && stop == 0)
                {
                    stop = 1;
                    nb = 0;
                }
                if (tableau[case_y][case_x] == 'J' && stop == 1)
                {
                    nb = nb + 1;
                    stop = 0;
                }
            }
        }
    }
    // Diagonale
    for (int case_y = 0; case_y < 7; case_y++)
    {
        stop = 0;
        for (int case_x = 0; case_x < 6; case_x++)
        {
        }
    }
    // D�tection partie nulle
    int nul = 0;
    if (stop_boucle == 0)
    {
        for (int case_x = 0; case_x < 6; case_x++)
        {

            if (tableau[0][case_x] == 'R' || tableau[0][case_x] == 'J')
            {
                nul = 1;
            }
            else
            {
                nul = 0;
            }
        }
    }
    if (nul == 1)
    {
        return 0;
    }
    // Si un ganant a �t� d�tect�
    if (stop_boucle == 1)
    {
        return joueur_gagnant;
    }
    else
    {
        nb = 0;
        return -1;
    }
}

// Fonction permatant de placer les pions dans le jeu selon la colonne choisie
// Revoit  1 si le gagnant est le joueur 1 apr�s avoir plac� un pion, 2 si c'est le joueur 2, 0 si la partie est nulle et -1 si la colonne choisie est remplie.
int placer(int colonne_choisie, char tableau[7][6], int joueur)
{
    int remplie = 0;
    if (tableau[colonne_choisie - 1][0] == 'R' || tableau[colonne_choisie - 1][0] ==
                                                      'J')
    {
        return -1;
    }
    for (int case_y = 5; case_y >= 0; case_y--)
    {
        if (tableau[colonne_choisie - 1][case_y] == ' ')
        {
            if (remplie != 1)
            {
                if (joueur == 1)
                {
                    tableau[colonne_choisie - 1][case_y] = 'R';
                }
                else if (joueur == 2)
                {
                    tableau[colonne_choisie - 1][case_y] = 'J';
                }
                remplie = 1;
            }
        }
    }
    return detecter(tableau);
}

// Fonction permattant d'afficher le tableau du jeu
void afficher_tableau(char tableau[7][6])
{
    for (int case_y = 0; case_y < 6; case_y++)
    {
        printf("%d.\t", 5 - case_y);
        for (int case_x = 0; case_x < 7; case_x++)
        {
            printf("\t%c |\t", tableau[case_x][case_y]);
        }
        printf("\n \t");
        for (int case_z = 0; case_z < 7; case_z++)
        {
            printf("---------------");
        }
        printf("\n");
    }
    for (int case_z = 0; case_z < 7; case_z++)
    {
        printf("\t%d.\t", case_z);
    }
}

// Fonction permetant d'initialiser le jeu
void jeu(char tableau_jeu[7][6])
{
    int termine = 0;
    srand(time(NULL));
    int joueur = rand() % 2 + 1;

    int colonne_choisie = 0;
    for (int case_x = 0; case_x < 7; case_x++)
    {
        for (int case_y = 0; case_y < 6; case_y++)
        {
            tableau_jeu[case_x][case_y] = ' ';
        }
    }
    while (termine == 0)
    {
        afficher_tableau(tableau_jeu);
        printf("\nAu joueur %d de placer une piece (ecrivez les coordonnees)\nSi vous voulez abandonner tapez 0\n\n", joueur);
        scanf("%d", &colonne_choisie);
        if (colonne_choisie > 7 || colonne_choisie < 0)
        {
            printf("\nMauvaise colone choisie\n");
        }
        else if (colonne_choisie == 0)
        {
            printf("\nAbandon...\n");
            termine = 1;
        }
        else if (!isdigit(colonne_choisie))
        {
            printf("\nEntrez un nombre.\n");
        }

        int etat = placer(colonne_choisie, tableau_jeu, joueur);
        if (etat == -1)
        {
            printf("Colonne remplie veulliez en choisir une autre.\n\n");
        }
        if (etat == 1)
        {
            afficher_tableau(tableau_jeu);
            printf("\nJOUEUR 1 a gagne\n");
            termine = 1;
        }
        else if (etat == 2)
        {
            afficher_tableau(tableau_jeu);
            printf("\nJOUEUR 2 a gagne\n");
            termine = 1;
        }
        else if (etat == 0)
        {
            afficher_tableau(tableau_jeu);
            printf("\nPARTIE NULLE\n");
            termine = 1;
        }
        if (joueur == 1)
        {
            joueur = 2;
        }
        else if (joueur == 2)
        {
            joueur = 1;
        }
    }
}

// Fonction permetant de d�mmarer le jeu et de donner ses peusdos
void debut(char tableau_jeu[7][6])
{
    char peusdo_1[MAX_LENGTH];
    char peusdo_2[MAX_LENGTH];
    size_t taille_peusdo_1;
    size_t taille_peusdo_2;
    char *positionEntree = NULL;

    printf("Bienvenue sur le puissance 4\n\n Entrez le peusdo du premier joueur\n");
    if (fgets(peusdo_1, MAX_LENGTH, stdin) != NULL)
    {
        positionEntree = strchr(peusdo_1, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            vider_buffer(); // Vidage du buffer qui va �viter le d�bordement en cas de longeur de peusdo > 20.
        }

        taille_peusdo_1 = strlen(peusdo_1);
        if (taille_peusdo_1 >= 2 && taille_peusdo_1 <= 20)
        {
            printf("Entrez le peusdo du deuxieme joueur\n");
            if (fgets(peusdo_2, MAX_LENGTH, stdin) != NULL)
            {
                positionEntree = strchr(peusdo_2, '\n');
                if (positionEntree != NULL)
                {
                    *positionEntree = '\0';
                }
                else
                {
                    vider_buffer(); // Vidage du buffer qui va �viter le d�bordement en cas de longeur de peusdo > 20.
                }
                taille_peusdo_2 = strlen(peusdo_2);
                if (taille_peusdo_2 >= 2 && taille_peusdo_2 <= 20)
                {
                    if (strcmp(peusdo_1, peusdo_2) != NULL)
                    {
                        jeu(tableau_jeu);
                    }
                    else
                    {
                        printf("Les peusdos doivent �tre diff�rents\n");
                    }
                }
                else
                {
                    printf("Veulliez saisir un peusdo entre 2 et carract�res\n");
                }
            }
            else
            {
                vider_buffer();
                fprintf(stderr, "Erreur fgets\n");
                return EXIT_FAILURE;
            }
        }
        else
        {
            printf("Veulliez saisir un peusdo entre 2 et carract�res\n");
        }
    }
    else
    {
        vider_buffer();
        fprintf(stderr, "Erreur fgets\n");
        return EXIT_FAILURE;
    }
}

// Fonction principale du programme
int main()
{
    char tableau_jeu[7][6];
    debut(tableau_jeu);
    return EXIT_SUCCESS;
}
