/**
 * La classe <code>MenuPrincipal</code> est utilisÃ©e pour choisir les options et aussi lancer une partie. Ici c'est la Vue du menu principal, donc c'est tout ce qui sera affichÃ© à l'Ã©cran de l'utilisateur.
 *  
 * @version 1.1
 * @author Rayan GRIB et Pierre BARBEY
 */

//Importation de tout les packages pour faire fonctionner la Vue.

import javax.swing.*;
import java.awt.*;
import java.util.Random;
import java.util.Arrays;
import java.awt.event.*;
import javax.swing.ImageIcon;

public class MenuPrincipal{

	//Crée la fenetre du menu principal

	/**
	*  Atribut qui contient la fenêtre du menu principal
	*/
	private JFrame fenetreMenu = new JFrame("SameGame : Menu principal");

	/** 
	* Atribut qui contient le bouton "Jouer".
	*/	
	private JButton jouer = new JButton("Jouer !");

	/**
	*  Atribut qui contient le bouton "Quitter".
	*/
	private JButton quitter = new JButton("Quitter");

	/** 
	* Atribut qui contient le bouton "Options".
	*/
	private JButton options = new JButton("Options");

	/**
	* Atribut qui contient le Modèle du menu principal pour y avoir accès depuis la vue (L'atribut est initialisé dans constructeur).
	*/ 
	private MenuPrincipalModel menuModel;

	/**
	* Ce constructeur permet de récupérer le Modèle du menu principal, d'y avoir accès depuis la Vue (ici). Ce constructeur est appelé dans la classe <code>SameGame</code>.
	* 
	*/
	public MenuPrincipal(MenuPrincipalModel menuModel){
		this.menuModel = menuModel;
	}

	//Tout ces attributs sont des attributs de classes car ils seront utilisés plus tard dans le code avec des méthodes get et set (voir plus bas).

	/**
	* La méthode permet d'afficher sur l'écran de du joueur, le menu principal avec les interactions rendues possibles (ActionListener) avec la classe <code>MenuPrincipalObs</code>. 
	*
	*/	
	public void afficherMenu(){
		JLabel infos = new JLabel();
		JPanel panneau = new JPanel();
		JPanel panneau2 = new JPanel();
		ImageIcon img = new ImageIcon("./pics/main/samegame.png");
		JLabel imgLabel = new JLabel(img, JLabel.CENTER);
		JPanel panneauBouton = new JPanel();
		JPanel panneauBas = new JPanel();
		GridLayout gestionnaireBouttons = new GridLayout(2,1);
		GridLayout gestionnaireBouttonBas = new GridLayout(1,2);
		GridLayout gestionnaireBoutton = new GridLayout(1,1);
		this.fenetreMenu.setIconImage(Toolkit.getDefaultToolkit().getImage("./pics/icon.png"));
		this.fenetreMenu.setResizable(false);
		this.fenetreMenu.setLocation(0,0);
		this.fenetreMenu.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		this.jouer.setFont(new Font("Arial", Font.BOLD, 16));
		this.options.setFont(new Font("Arial", Font.BOLD, 12));
		this.quitter.setFont(new Font("Arial", Font.BOLD, 12));
		infos.setFont(new Font("Arial", Font.BOLD , 12));
		infos.setOpaque(true);
		infos.setBackground(new Color(105,105,105));
		infos.setForeground(Color.WHITE);
		this.jouer.setBackground(new Color(65,105,225));
		this.jouer.setForeground(Color.WHITE);
		this.options.setBackground(Color.WHITE);
		this.quitter.setBackground(Color.WHITE);
		panneau.add(jouer);
		panneauBas.add(options);
		panneauBas.add(quitter);
		panneau.setLayout(gestionnaireBoutton);
		panneauBas.setLayout(gestionnaireBouttonBas);
		panneauBouton.setLayout(gestionnaireBouttons);
		panneauBouton.add(panneau);
		panneauBouton.add(panneauBas);
		infos.setText(this.menuModel.getPhrases()[new Random().nextInt(this.menuModel.getPhrases().length)]);
		infos.setHorizontalAlignment(JLabel.CENTER);
		this.fenetreMenu.add(infos, BorderLayout.NORTH);
		this.fenetreMenu.add(panneauBouton, BorderLayout.SOUTH);
		panneau2.add(imgLabel);
		this.fenetreMenu.add(panneau2, BorderLayout.CENTER);
		this.fenetreMenu.pack();
		this.fenetreMenu.setLocationRelativeTo(null);
		this.fenetreMenu.setVisible(true);
	}

	/**
	* Méthode (un getter) qui permet d'accèder à la fenetre du menu principal (qui a un accès en private). 
	*
	* @return La fenetre du menu principal.
	*/
	public JFrame getFenetreMenu(){
		return this.fenetreMenu;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au bouton "Jouer" du menu principal (qui a un accès en private). 
	*
	* @return Le bouton "Jouer" du menu principal.
	*/
	public JButton getJouerButton(){
		return this.jouer;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au bouton "Quitter" du menu principal (qui a un accès en private). 
	*
	* @return Le bouton "Quitter" du menu principal.
	*/
	public JButton getQuitterButton(){
		return this.quitter;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au bouton "Options" du menu principal (qui a un accès en private). 
	*
	* @return Le bouton "Options" du menu principal.
	*/
	public JButton getOptionsButton(){
		return this.options;
	}
}