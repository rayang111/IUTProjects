import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import java.io.IOException;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;


public class Regles{
	/**
    * Attribut qui représente le bouton permettent de retourner sur le jeu. 
    */
	public  JButton quitterRegles = new JButton("Retourner sur le jeu");
	/**
    * Attribut qui affiche le titre des règles. 
    */
	public  JTextArea reglesTexte = new JTextArea("Voici les Règles du jeu SameGame");
	/**
    * Attribut qui appel la classe Affichage. 
    */
	private Affichage afficher;
	/**
    * Attribut qui appel la classe ReglesModel. 
    */
	private ReglesModel reglesModel;
	/**
    * Attribut qui represente la fenetre des regles. Ces une fenetre de dialogue car elle pertment a cette derniere de rester en focus tous le temps. 
    */
	private JDialog fenetreRegles;

	/**
    *  Ce constructeur est appelé dans la classe <code>Jeu</code>.
	*  @param reglesModel fait appel la classe ReglesModel
	*  @param afficher fait appel la classe Affichage
    */
	public Regles(ReglesModel reglesModel, Affichage afficher){
		this.afficher = afficher;
		this.reglesModel = reglesModel;
	}


	/**
	* La méthode permet d'afficher les règles. 
	*
	*/	
	public void afficherRegles(){
		fenetreRegles = new JDialog(afficher.getFenetreJeu(),"SameGame : Règles", true);
    	reglesTexte.setEditable(false);
		fenetreRegles.setIconImage(Toolkit.getDefaultToolkit().getImage("./pics/icon.png"));
		fenetreRegles.setLocation(0,0);
		fenetreRegles.setBackground(Color.DARK_GRAY);
		fenetreRegles.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		fenetreRegles.setResizable(false);
		quitterRegles.setBackground(Color.DARK_GRAY);
		quitterRegles.setForeground(Color.WHITE);
		quitterRegles.setOpaque(true);
		reglesTexte.setText(reglesModel.getTexteComplet());
		reglesTexte.setBackground(Color.DARK_GRAY);
		reglesTexte.setOpaque(true);
		reglesTexte.setForeground(Color.WHITE);
		reglesTexte.setFont(new Font("Arial", Font.BOLD, 12));
		fenetreRegles.add(reglesTexte, BorderLayout.CENTER);
		fenetreRegles.add(quitterRegles, BorderLayout.SOUTH);
		fenetreRegles.pack();
		fenetreRegles.setLocationRelativeTo(null);
		fenetreRegles.setVisible(true);
	}

	/**
	* Méthode (un getter) qui permet d'accèder à l'attribut qui represente la fenetre des regles (qui a un accès en private). 
	*
	* @return la fenetre des regles.
	*/
	public JDialog getFenetreRegles(){
		return this.fenetreRegles;
	}

	/**
	* Méthode (un getter) qui permet d'accèder à l'attribut qui représente le bouton permettent de retourner sur le jeu (qui a un accès en private). 
	*
	* @return le bouton retour au menu.
	*/
	public JButton getQuitterReglesButton(){
		return this.quitterRegles;
	}
}