# blocus : fichier Makefile

# CHAPITRE 1 : BUT FINAL

but : jeu_blocus

# CHAPITRE 2 : VARIABLES

OFILES = menu.o \
         jeu.o \
         main.o

CC = gcc

CFLAGS = -lgraph

# CHAPITRE 3 : DEPENDANCES (REGLES IMPLICITES)

menu.o : menu.h menu.c
jeu.o : jeu.h jeu.c
main.o : menu.h jeu.h

#CHAPITRE 4 : DEPENDANCES AVEC COMMANDES


jeu_blocus : $(OFILES)
	$(CC) $(CFLAGS) -o jeu_blocus $(OFILES)

#CHAPITRE 5 : NETTOYAGE DES FICHIERS GENERES

clean :
	-rm -f ${OFILES}

#CHAPITRE 6 : BUTS FACTICES

.PHONY : but clean

run :
	./jeu_blocus

