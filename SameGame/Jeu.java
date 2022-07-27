/**
 * La classe <code>Jeu</code> est utilisÃ©e pour gerer une partie en cours et sa fin. Cette Classe fait partie de la Classe Jeu, c'est à dire, Affichage (Vue), JeuObs (Controlleur) et cette Classe qui est le Model. C'est ici où on gère les données d'une partie.
 *  
 * @version 1.1
 * @author Rayan GRIB et Pierre BARBEY
 */

import java.awt.*;
import java.util.Arrays;
import java.awt.event.*;
import java.io.File;
import java.io.IOException;
import java.io.*;

public class Jeu{

	/**
	*	Attribut qui permet de savoir si le jeu est en pause ou non.
	*/
	private boolean isPaused = false;

	/**
	*	Attribut qui permet de savoir si on a quitté le jeu ou non.
	*/
	private boolean quitter = true;

	/**
	*	Attribut qui permet de savoir si on a gagné ou non.
	*/
	private boolean victoire = false; 

	/**
	*	Attribut qui contient le score du joueur
	*/
	private int score = 0;

	/**
	*	Attribut qui contient le meilleur score du jeu (durant la partie)
	*/
	private int meilleurScore = 0;

	/**
	*	Attribut qui contient le score que rapporte un groupe (qui a été détruit)
	*/
	private int scoregrp = 0;

	/**
	*	Attribut qui contient le nombre de groupes pour le score
	*/
	private int nbGroupes = 0;

	/**
	*	Attribut qui contient une référence au Contrôlleur du menu d'options, <code>OptionsObs</code>
	*/
	private OptionsObs menuOptionsObs;

	/**
	*	Attribut qui permet de savoir si un groupe est possible ou non.
	*/
	private boolean grppossible;

	/**
	*	Attribut qui contient les coordonnées de la case survolées (en hauteur)
	*/
	private int posinitiale_i=-1;

	/**
	*	Attribut qui contient les coordonnées de la case survolées (en largeur)
	*/
	private int posinitiale_j=-1;

	/**
	*	Attribut qui contient le tableau des groupes (permet de savoir ou se situe un groupe avec true et des false)
	*/
	private boolean[][] tab_groupe=new boolean[10][15];

	/**
	*	Attribut qui contient le tableau des groupes identifiés pour un numéro (les groupes sont identifiés par un numéro) 
	*/
	private int[][] tab_groupenb=new int[10][15];

	/**
	*	Attribut qui peremt de compter le nombre de groupes en comptant le nombre de différents dans ce tableau
	*/
	private int[] nb = new int[150];

	/**
	*	Attribut qui contient le nombre de blocs qu'a un groupe sélectionné
	*/
	private int nb_blocs = 1;

	/**
	*	Attribut qui permet de savoir si il reste des groupes ou non
	*/
	private boolean rester = false;

	/**
	*	Attribut qui permet de savoir si un groupe est possible d'être "créee"
	*/
	private boolean possible = true;

	/**
	*	Attribut qui contient le nombre de groupes restant à éléminer
	*/
	private int nbgroup = 0;

	/**
	*	Attribut qui contient une référence à la classe Chargement, <code>Chargement</code>
	*/	
	private Chargement charger;

	/**
	* Ce constructeur permet de récupérer le Contrôlleur de <code>OptionsObs</code> et aussi la Vue de jeu <code>Affichage</code>, d'y avoir accès depuis le Modèle <code>Jeu</code> (ici). Ce constructeur est appelé dans la classe <code>MenuPrincipalObs</code>.
	* 
	*/
	public Jeu(OptionsObs menuOptionsObs, Chargement charger){
		this.menuOptionsObs = menuOptionsObs;
		this.charger = charger;

	}

	/**
	*	Méthode qui permet lancer le jeu
	*/
	public void jeu(){
		String musiqueChemin ="";
		quitter = false;
		victoire = false;
		this.setScore(0);
	}

	/**
	*	Méthode qui permet de lire le meilleur score du jeu.
	*	@throws IOException Si il y a une erreur de lecture dans le fichier meilleurScore.bin ou/et une erreur de fermeture du fichier ou si la création de ce fichier (si il n'a pas été trouvé) a échoué.
	*	@throws FileNotFoundException Si le fichier n'as pas été trouvé dans l'ordinateur de l'utilisateur
	*/
	public void meilleurScoreLecture(){
		File fichierMeilleurScore = new File("./meilleurScore.bin");
		try{
			FileInputStream streamMeilleurScore = new FileInputStream(fichierMeilleurScore);
    		DataInputStream flux = new DataInputStream(streamMeilleurScore);
			try{
				while(flux.available() > 0){
					meilleurScore = flux.readInt();
				}
			}catch(IOException exec){
				System.err.println("Erreur de lecture dans le fichier meilleurScore.bin...");
			}
			try{
				flux.close();
			}catch(IOException exec){
				System.err.println("Erreur lors de la fermeture en lecture du fichier meilleurScore.bin...");
			}
		}catch(FileNotFoundException exec){
			System.err.println("Fichier meilleutScore.bin introuvable créeation d'un nouveau fichier du même nom (le meilleur score a été perdu...)");
			try{
				fichierMeilleurScore.createNewFile();
			} catch(IOException exec2){
				System.err.println("Fichier meilleutScore.bin n'a pas pû être crée...");
			}
		}
	}

	/**
	*	Méthode qui rénintialise à false, les valeurs de la grille de boolean (true/false) qui permet d'identifier les groupes.
	*/
	public void deleteGroupe(){
		nb_blocs = 1;
		for(int y=0;y<10;y++){
			for(int t=0;t<15;t++){
				if(charger.getTableauJeu()[y][t]!='.'){
					tab_groupe[y][t]=false;
				}
			}
		}
		setScoreGroupe(0);
		posinitiale_i=-1;
		posinitiale_j=-1;
		grppossible=false;
	}

	/**
	*	Méthode qui identifie les groupes et qui compte le nombre de blocs du groupe.
	* @param i position x sur le tableau de la case survolée
	* @param j position y sur le tableau de la case survolée
	*/
	public void groupe(int i, int j){

		if(charger.getTableauJeu()[i][j]!='.'){
			char couleur= charger.getTableauJeu()[i][j];
			setNombreGroupes(1);
			if(i<9){
				if((charger.getTableauJeu()[i+1][j]==couleur)&&(tab_groupe[i+1][j]==false)){
					groupepossible(i,j);
					resetScoreGroupe(1);
					tab_groupe[i+1][j]=true;
					nb_blocs = nb_blocs + 1;
					groupe(i+1,j);				
				}
			}
			if(j<14){
				if((charger.getTableauJeu()[i][j+1]==couleur)&&(tab_groupe[i][j+1]==false)){
					groupepossible(i,j);
					resetScoreGroupe(1);
					tab_groupe[i][j+1]=true;
					nb_blocs = nb_blocs + 1;
					groupe(i,j+1);				
				}
			}
			if(i>0){
				if((charger.getTableauJeu()[i-1][j]==couleur)&&(tab_groupe[i-1][j]==false)){
					groupepossible(i,j);
					resetScoreGroupe(1);
					tab_groupe[i-1][j]=true;
					nb_blocs = nb_blocs + 1;
					groupe(i-1,j);				
				}
			}

			if(j>0){
				if((charger.getTableauJeu()[i][j-1]==couleur)&&(tab_groupe[i][j-1]==false)){
					groupepossible(i,j);
					resetScoreGroupe(1);
					tab_groupe[i][j-1]=true;
					nb_blocs = nb_blocs + 1;
					groupe(i,j-1);				
				}
			} 
		}
		
	}

	/**
	*	Méthode qui permet de faire chuter les blocs lorsqu'un groupe est détruit.
	*/
	public void groupeDes(){
		for(int i = 0; i < charger.getTableauJeu().length; i++){
			for(int y =0; y < charger.getTableauJeu()[i].length; y++){
		if(charger.getTableauJeu()[i][y]!='.'){
			if(i<9){
				for(int z =0; z < charger.getTableauJeu().length; z++){
				if(charger.getTableauJeu()[i+1][y] == '.'&& charger.getTableauJeu()[i][y] != '.'){
					charger.getTableauJeu()[i+1][y] = charger.getTableauJeu()[i][y];
					charger.getTableauJeu()[i][y] = '.';		
				}
		}
					}
				}
			}
		}
	}

	/**
	*	Méthode qui permet de faire décaler les blocs vers la gauche lorsqu'une colonne est vide.
	*/
	public void groupeDes2(){

			for(int i = 0; i < charger.getTableauJeu().length; i++){
					for(int y =0; y < charger.getTableauJeu()[i].length; y++){
				if(y>0){
					for(int e = 0; e < charger.getTableauJeu().length;e++){
						if(charger.getTableauJeu()[e][y-1] == '.'){
							possible = true;
						} 
						if (charger.getTableauJeu()[e][y-1] == 'R' || charger.getTableauJeu()[e][y-1] == 'B' || charger.getTableauJeu()[e][y-1] == 'V'){
							possible = false;
							e = charger.getTableauJeu().length+1000;
						}
					}
					if(possible == true){
						for(int z =0; z < charger.getTableauJeu()[i].length; z++){
							if(charger.getTableauJeu()[i][y-1] == '.'&& charger.getTableauJeu()[i][y] != '.'){
							for(int e=0; e<charger.getTableauJeu().length;e++){
								charger.getTableauJeu()[e][y-1] = charger.getTableauJeu()[e][y];
								charger.getTableauJeu()[e][y] = '.';
								}
							}
						}
					}
				}
			}
		}
	}	

	/**
	*	Méthode qui permet d'afficher la grille des groupes.
	*/
	public void getGroup(){
		System.out.println("DEBUT GRP");
		for(int i=0;i<tab_groupe.length;i++){
			for(int y=0;y<tab_groupe[i].length;y++){
				System.out.print(tab_groupe[i][y]);
				System.out.print(" ");
			}
			System.out.println("");
		}
		System.out.println("FIN GRP");
	}

	/**
	*	Méthode qui permet redéfinir la grille des groupes.
	*/
	public void setGroup(){
		for(int i=0;i<tab_groupe.length;i++){
			for(int y=0;y<tab_groupe[i].length;y++){
				tab_groupe[i][y] = false;
			}
		}
	}

	/**
	*	Méthode qui permet de dire si il s'agit bien d'un groupe.
	*	@param i position x sur le tableau de la case survolée
	*	@param j position y sur le tableau de la case survolée
	*/
	public void groupepossible(int i,int j){
		if((posinitiale_i==-1)&&(posinitiale_j==-1)){
			posinitiale_i=i;
			posinitiale_j=j;
			resetScoreGroupe(1);
			tab_groupe[posinitiale_i][posinitiale_j]=true;
			grppossible=true;
		}
	}


	/**
	*	Méthode qui permet de dire si il reste des groupe ou non
	*/
	public void groupeRester(){
		for(int i = 0; i < charger.getTableauJeu().length && rester == true; i++){
			for (int y = 0; y < charger.getTableauJeu()[i].length && rester == true ; y++) {
				if(charger.getTableauJeu()[i][y] != '.'){
					if(i<9 && i>0 && y<14 && y>0){
						if((charger.getTableauJeu()[i+1][y]=='.' || (charger.getTableauJeu()[charger.getTableauJeu().length-1][y-1]=='.'))){
							rester = true;
						} else{
							rester = false;
						}
					}
				}
			}
		}
	}

	/**
	*	Méthode qui compter le nombre de groupe restant dans le jeu.
	*/
	public void nbGroup(){
		int numgroup = 1;
		nbgroup = 0;
		for(int i=0; i<tab_groupe.length;i++){
			Arrays.fill(tab_groupenb[i], 0);
		}
		  for(int i=0; i < charger.getTableauJeu().length; i++){
			for (int y =0; y < charger.getTableauJeu()[i].length ; y++) {
				deleteGroupe();
				groupe(i,y);
				boolean testGrp = grppossible;
				for(int e = 0; e < tab_groupe.length; e++){
					for(int z = 0; z < tab_groupe[e].length; z++){
						if(tab_groupe[e][z] == true){
							tab_groupenb[e][z] = numgroup;
						}
					}
				}
				numgroup = numgroup + 1;
			}
		}
				Arrays.fill(nb, 0);
				int r = 0;
				for(int e = 0; e < tab_groupe.length; e++){
					for(int z = 0; z < tab_groupe[e].length; z++){
							nb[r] = tab_groupenb[e][z];
							r = r + 1;
					}
				}
				for(int a = 0; a < nb.length; a++){
					int val = nb[a];
					for (int b =0; b < nb.length ; b++) {
							if(nb[b] == val && b != a){
								nb[a] = 0;
							}			
						}			
				}
				for(int e = 0; e < nb.length; e++){
					if(nb[e] != 0){
						nbgroup = nbgroup + 1;
					}
				}

	}

	/**
	*	Méthode qui d'afficher les groupes identifiés par des numéros
	*/
	public void getGroup2(){
		System.out.println("DEBUT NBGRP");
		for(int i=0;i<tab_groupenb.length;i++){
			for(int y=0;y<tab_groupenb[i].length;y++){
				System.out.print(tab_groupenb[i][y]);
				System.out.print(" ");
			}
			System.out.println("");
		}
		System.out.println("FIN NBGRP");
	}

	/**
	*	Méthode qui permet de mettre à jour le score
	*/
	public void score(){
		score = score + (int) Math.pow((scoregrp - 2),2);
	}


	public boolean getIsPaused(){
		return this.isPaused;
	}
	public boolean getQuitter(){
		return this.quitter;
	}
	public boolean getVictoire(){
		return this.victoire;
	}
	public void setQuitter(boolean etat){
		this.quitter = etat;
	}
	public void setIsPaused(boolean etat){
		this.isPaused = etat;
	}
	public void setVictoire(boolean etat){
		this.victoire = etat;
	}
	public int getScore(){
		return this.score;
	}
	public void setScore(int nombre){
		this.score = nombre;
	}
	public void resetScore(int nombre){
		this.score = this.score + nombre;
	}
	public int getScoreGroupe(){
		return this.scoregrp;
	}
	public void resetScoreGroupe(int nombre){
		this.scoregrp = this.scoregrp + nombre;
	}
	public void setScoreGroupe(int nombre){
		this.scoregrp = nombre;
	}
	public int getNombreGroupes(){
		return this.nbGroupes;
	}
	public void setNombreGroupes(int nombre){
		this.nbGroupes = this.nbGroupes + nombre;
	}
	public int getMeilleurScore(){
		return this.meilleurScore;
	}
	public void setMeilleurScore(int score){
		this.meilleurScore = score;
	}
	public boolean getGroupePossible(){
		return this.grppossible;
	}
	public int getPositionInitialeI(){
		return this.posinitiale_i;
	}   
	public int getPositionInitialeJ(){
		return this.posinitiale_j;
	}
	public boolean[][] getTableauGroupe(){
		return this.tab_groupe;
	}
	public int[][] getTableauGroupeNombre(){
		return this.tab_groupenb;
	}
	public boolean getRester(){
		return this.rester;
	}
	public boolean getPossible(){
		return this.possible;
	}
	public int getNbGroupes(){
		return this.nbgroup;
	}
	public int getNombreBlocs(){
		return this.nb_blocs;
	}
	public void setTableauGroupe(char val, int i, int y){
		charger.getTableauJeu()[i][y] = val;
	}

}