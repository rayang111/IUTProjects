/**
 * La classe <code>Observateur</code> est utilisÃ©e comme Controlleur de la Classe Jeu (JeuModel, JeuVue). Cette Classe permet de gérer les actions du joueur durant une partie (ceci nous permet d'éviter d'utiliser une boucle "infinie"). Ce Controlleur communique avec le Model (JeuModel) et la Vue (JeuVue).
 *  
 * @version 1.1
 * @author Rayan GRIB
 * @author Pierre BARBEY
 */
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;
import java.io.File;
import java.io.IOException;

public class Observateur implements MouseListener{
	/**
    * Attribut qui est utilisé dans les boucles. 
    */
	private int a=0;
	/**
    * Attribut qui est utilisé dans les boucles. 
    */
	private int b=0;
	/**
    * Attribut qui est utilisé dans les boucles. 
    */
	private int c;
	/**
    * Attribut qui est utilisé dans les boucles. 
    */
	private int d;
	/**
    * Attribut qui un tableau représentent les images affiché sue le jeu. 
    */
	private JLabel[][] f=new JLabel[10][15];
	/**
    * Attribut qui empeche de cliqué plusieur fois sur la meme case sans bouger la souris. 
    */
	private boolean isCliquee = false;
	/**
    * Attribut qui indique si il s'agit d'un groupe. 
    */
	private boolean testGrp;
	/**
    * Attribut qui appel la classe Chargement. 
    */
	private Chargement chargerJeu;
	/**
    * Attribut qui appel la classe Affichage. 
    */
	private Affichage afficher;
	/**
    * Attribut qui appel la classe OptionsObs. 
    */
	private OptionsObs menuOptionsObs;
	/**
    * Attribut qui appel la classe Jeu. 
    */
	private Jeu jeu;
	/**
    * Attribut qui appel la classe JeuObs. 
    */
	private JeuObs jeuObs;

	/**
    *  Ce constructeur est appelé dans la classe <code>Jeu</code>.
    *  @param c tableau représentent les images affiché sue le jeu
    *  @param i position x sur le tableau de la case survolée
	*  @param j position y sur le tableau de la case survolée
	*  @param afficher fait appel la classe Affichage
	*  @param chargerJeu fait appel la classe Chargement
	*  @param jeu fait appel la classe Jeu
	*  @param menuOptionsObs fait appel la classe OptionsObs
	*  @param jeuObs fait appel la classe JeuObs
    */
	public Observateur(JLabel[][] c, int i, int j, Affichage afficher, Chargement chargerJeu, Jeu jeu, OptionsObs menuOptionsObs, JeuObs jeuObs){
		this.f=c;
		this.c=i;
		this.d=j;
		this.afficher = afficher;
		this.chargerJeu = chargerJeu;
		this.menuOptionsObs = menuOptionsObs;
		this.jeu = jeu;
		this.jeuObs = jeuObs;
	}
	/**
    * Cette redéfinition de la méthode MouseListener de l'Interface <code>MouseListener</code> permet de gèrer lorsque l'utilisateur clique sur un composent
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void mouseClicked(MouseEvent evenement){
		if(isCliquee == false){
			isCliquee = true;
			jeu.deleteGroupe();
			jeu.groupe(c,d);
			jeu.score();
			if(testGrp==true){
				for(int a=0;a<10;a++){
					for(int b=0;b<15;b++){
						if(jeu.getTableauGroupe()[a][b]==true){
							jeuObs.detruire(a,b);
							jeu.setTableauGroupe('.', a, b);
							this.f[a][b].setBackground(Color.BLACK);
							this.f[a][b].setOpaque(false);
						}
					}
				}
	   			afficher.getScoreTexte().setText("Score : " + Integer.toString(jeu.getScore()));
				for(int i = 0;i<chargerJeu.getTableauJeu().length;i++){
					for (int y=0;y<chargerJeu.getTableauJeu()[i].length ; y++) {
							jeu.groupeDes();
							jeu.groupeDes2();
							afficher.reactualisation();
					}
				}
				jeu.nbGroup();
				if(jeu.getNbGroupes() == 0){
					jeu.groupeRester();	
					if(jeu.getRester() == false){
						jeu.setQuitter(true);
						FinModel finModel = new FinModel();
						Fin fin = new Fin(finModel, jeu);
						FinObs finObs = new FinObs(fin, finModel, afficher, jeu, menuOptionsObs);
					}
					
				}

				
			}
		}

		
	}
	/**
    * Cette redéfinition de la méthode MouseListener de l'Interface <code>MouseListener</code> permet de gèrer lorsque l'utilisateur survole un composent
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override          
	public void mouseEntered(MouseEvent evenement){
		jeu.groupe(c,d);
		testGrp=jeu.getGroupePossible();
		for(int a=0;a<10;a++){
			for(int b=0;b<15;b++){
				if(jeu.getTableauGroupe()[a][b]==true){
					Color couleur = Color.WHITE;
					try{
						if(menuOptionsObs.getChoixTheme() == 1){
							couleur = Color.CYAN;
						}
						if(menuOptionsObs.getChoixTheme() == 2){
							couleur = Color.RED;
						}
					}catch(NullPointerException exec){
						couleur = Color.CYAN;
					}
					this.f[a][b].setBackground(couleur);
					this.f[a][b].setOpaque(true);
				}
			}
		}
	}
	/**
    * Cette redéfinition de la méthode MouseListener de l'Interface <code>MouseListener</code> permet de gèrer lorsque l'utilisateur arrete de survoler un composent
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override          
	public void mouseExited(MouseEvent evenement){
		isCliquee = false;
		jeu.deleteGroupe();
		testGrp=jeu.getGroupePossible();
		for(int a=0;a<10;a++){
			for(int b=0;b<15;b++){
				this.f[a][b].setBackground(Color.BLACK);
				this.f[a][b].setOpaque(false);
				
			}
		}
	}
	/**
    * Cette redéfinition de la méthode MouseListener de l'Interface <code>MouseListener</code> permet de gèrer lorsque l'utilisateur appui sur un bouton 
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override           
	public void mousePressed(MouseEvent evenement){

	}
	/**
    * Cette redéfinition de la méthode MouseListener de l'Interface <code>MouseListener</code> permet de gèrer lorsque l'utilisateur relache sur un bouton 
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override          
	public void mouseReleased(MouseEvent evenement){}

	
}