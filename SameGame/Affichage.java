/**
 * La classe <code>Affichage</code> est utilisÃ©e afficher le jeu après le chargement. Cette Classe fait partie de la Classe Jeu, c'est à dire JeuObs (Controlleur) et Observateur (Controlleur), Jeu (Modèle) et cette Classe qui est la Vue. 
 * C'est cette dernière qui intéragie avec l'utilisateur grâce à des composants graphiques de swing et AWT. Cette Vue communique qu'avec les Controlleurs JeuObs et Observateur.
 *  
 * @version 1.1
 * @author Rayan GRIB et Pierre BARBEY
 */

//Importation de tout les packages que la Vue a besoin

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Arrays;
import java.awt.Graphics;
import javax.swing.JComponent;
import javax.swing.ImageIcon;


public class Affichage{

	/**
	*	Attribut qui contient la fenêtre du jeu
	*/
	private JFrame fenetreJeu = new JFrame("SameGame : Partie en Cours");

	/**
	*	Attribut qui contient le bouton "Pause" du jeu
	*/
	private JToggleButton boutonPause = new JToggleButton("Pause");

	/**
	*	Attribut qui contient le bouton "Quitter" du jeu
	*/
	private JButton boutonQuitter = new JButton("Quitter");

	/**
	*	Attribut qui contient le texte d'encouragement qui s'affichera sur le haut de la fenêtre du jeu
	*/
	private  JLabel texte = new JLabel();

	/**
	*	Attribut qui contient le fond pour le thème "ChorusWorld".
	*/
	private Image fond = Toolkit.getDefaultToolkit().getImage("./pics/levels/fond.png");

	/**
	*	Attribut qui contient le fond pour le thème "Horrorcore".
	*/
	private Image fond2 = Toolkit.getDefaultToolkit().getImage("./pics/levels/fond_horreur.png");

	/**
	*	Attribut qui contient le fond du menu pause.
	*/
	private Image fondPause = Toolkit.getDefaultToolkit().getImage("./pics/pause.gif");

	/**
	*	Attribut qui contient l'image d'un bloc
	*/
	private ImageIcon imgBlock;

	/**
	*	Attribut qui contient le boutton "Tricher" du jeu
	*/
	private JButton triche = new JButton("Tricher (C'est pas bien !)");

	/**
	*	Attribut qui permet de savoir si le jeu est déja chargé ou non
	*/
	private int dejaharger=0;

	/**
	*	Attribut qui contient le bouton "Règles" du jeu
	*/
	private JButton regles = new JButton("Règles");

	/**
	*	Attribut qui contient le Modèle du jeu
	*/
	private Jeu jeuModel;

	/**
	*	Attribut qui contient une référence à la classe Chargement
	*/
	private Chargement chargerJeu;

	/**
	*	Attribut qui contient le Modèle du menu des options
	*/
	private OptionsModel menuOptionsModel;

	/**
	*	Attribut qui contient le Contrôlleur du menu des options
	*/
	private OptionsObs menuOptionsObs;

	/**
	*	Attribut qui contient le score (JLabel) qui est affiché sur le haut de la fenêtre
	*/
	private JLabel scoreTexte;

	/**
	*	Attribut qui contient le panneau où les blocs s'afficheront
	*/
	private JPanel panneau2 = new JPanel(){
		/**
		*	Méthode qui permet de mettre un fond sur le panneau où les blocs s'affichent
		*	@param pinceau un attribut de type Graphics
		*	@throws NullPointerException si aucun thème n'a été choisi (On suppose donc que le joueur a choisi le thème "ChorusWorld")
		*/
		 protected void paintComponent(Graphics pinceau){
		 	try{
		 		if(menuOptionsObs.getChoixTheme() == 1){
    				pinceau.drawImage(fond, 0, 0, panneau2.getWidth(), panneau2.getHeight(), this);
    			}
    			if(menuOptionsObs.getChoixTheme() == 2){
    				pinceau.drawImage(fond2, 0, 0, panneau2.getWidth(), panneau2.getHeight(), this);
    			}
    		}catch(NullPointerException exec){
    			pinceau.drawImage(fond, 0, 0, panneau2.getWidth(), panneau2.getHeight(), this);
    		}
 		}
	};

	/**
	*	Attribut qui contient le panneau du menu pause
	*/
	private JPanel panneauPause = new JPanel(){
		/**
		*	Méthode qui permet de mettre un fond sur le panneau du menu pause
		*	@param pinceau un attribut de type Graphics
		*/
		protected void paintComponent(Graphics pinceau){
				pinceau.drawImage(fondPause, 0, 0, panneauPause.getWidth(), panneauPause.getHeight(), this);
 		}
	};

	/**
	*	Attribut qui contient un tableau de JLabel où les blocs y sont stocké
	*/	
	private JLabel[][] tabJeuLabel;

	/**
	* Ce constructeur permet de récupérer le Modèle du jeu, d'y avoir accès depuis la Vue (ici) Aussi de récupérer des données de <code>Chargement</code> pour les afficher.
	* Pour récupérer aussi d'autres données venant du menu des options (<code>OptionsModel</code> et <code>OptionsObs</code>).
	* Ce constructeur est appelé dans la classe <code>JeuObs</code>.
	* 
	*/
	public Affichage(Jeu jeuModel, Chargement chargerJeu, OptionsModel menuOptionsModel, OptionsObs menuOptionsObs){
		this.jeuModel = jeuModel;
		this.chargerJeu = chargerJeu;
		this.menuOptionsModel = menuOptionsModel;
		this.menuOptionsObs = menuOptionsObs;
	}

	/**
	* Méthode qui permet d'afficher la fenêtre du jeu avec ses composants graphiques
	* @throws NullPointerException si aucun thème n'a été choisi (On suppose donc que le joueur a choisi le thème "ChorusWorld")
	*/
	public void afficher(){
		this.tabJeuLabel = new JLabel[chargerJeu.getTableauJeu().length][chargerJeu.getTableauJeu()[0].length];
		this.scoreTexte = new JLabel("Score : " + Integer.toString(jeuModel.getScore()));
		JPanel panneau = new JPanel();
		JPanel panneau3 = new JPanel();
		GridLayout gestionnaire = new GridLayout(chargerJeu.getTableauJeu().length,chargerJeu.getTableauJeu()[0].length);
		GridLayout gestionnaireHaut = new GridLayout(1,3);
		GridLayout gestionnaireBas = new GridLayout(1,4);
		fenetreJeu.setIconImage(Toolkit.getDefaultToolkit().getImage("./pics/icon.png"));
		fenetreJeu.setLocation(0,0);
		fenetreJeu.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		fenetreJeu.setResizable(true);
		fenetreJeu.setMinimumSize( new Dimension(1000, 800));
		panneau2.setLayout(gestionnaire);
		panneau.add(boutonPause);
		if(menuOptionsModel.getChoixAutoriserTriche() == true){
			triche.setVisible(true);
			panneau.add(triche);

		} else{
			triche.setVisible(false);
		}
		triche.setBackground(Color.WHITE);
		regles.setBackground(Color.WHITE);
		panneau3.setLayout(gestionnaireHaut);
		panneau.setLayout(gestionnaireBas);
		panneau.add(regles);
		panneau.add(boutonQuitter);
		try{
			if(menuOptionsObs.getChoixTheme() == 1){
				texte.setText(" Bon courage ! Détruisez les cubes.");
			}
			if(menuOptionsObs.getChoixTheme() == 2){
				texte.setText(" ARGHHHHHHHH ! Pulvérisez tout... ");
			}
		}catch(NullPointerException exec){
			texte.setText(" Bon courage ! Détruisez les cubes.");
		}
		panneau3.add(texte);
		texte.setHorizontalAlignment(JLabel.CENTER);
		scoreTexte.setHorizontalAlignment(JLabel.CENTER);
		boutonQuitter.setHorizontalAlignment(JButton.CENTER);
		boutonPause.setHorizontalAlignment(JButton.CENTER);
		regles.setHorizontalAlignment(JButton.CENTER);
		triche.setHorizontalAlignment(JButton.CENTER);
		panneau3.add(scoreTexte);
		boutonQuitter.setBackground(Color.WHITE);
		boutonPause.setBackground(Color.WHITE);
		fenetreJeu.add(panneau, BorderLayout.SOUTH);
		fenetreJeu.add(panneauPause, BorderLayout.EAST);
		panneauPause.setVisible(false);
		fenetreJeu.add(panneau2, BorderLayout.CENTER);
		panneau2.setPreferredSize(new Dimension(1000,800));
		panneauPause.setPreferredSize(new Dimension(1000,800));
		fenetreJeu.add(panneau3, BorderLayout.NORTH);
		scoreTexte.setFont(new Font("Arial", Font.BOLD, 14));
		scoreTexte.setForeground(Color.WHITE);
		scoreTexte.setBackground(new Color(65,105,225));
		scoreTexte.setOpaque(true);
		texte.setFont(new Font("Arial", Font.ITALIC, 12));
		fenetreJeu.pack();
		fenetreJeu.setLocationRelativeTo(null);
		fenetreJeu.setVisible(true);
		this.afficherJeu();
	}

	/**
	* Méthode qui permet d'afficher le le jeu (les blocs) avec leurs images selon le thème choisi et surtout le type de bloc (R, V ou B)
	* @throws NullPointerException si aucun thème n'a été choisi (On suppose donc que le joueur a choisi le thème "ChorusWorld")
	*/
	public void afficherJeu(){
		int i = 0;
		int y = 0;
		for(i=0;i<chargerJeu.getTableauJeu().length;i++){
			for(y=0;y<chargerJeu.getTableauJeu()[i].length;y++){
				if(chargerJeu.getTableauJeu()[i][y] == 'R'){
					try{
						if(menuOptionsObs.getChoixTheme() == 1){
							imgBlock = new ImageIcon("./pics/classic/red.png");
						}
						if(menuOptionsObs.getChoixTheme() == 2){
							imgBlock = new ImageIcon("./pics/horror/red.png");
						}
					}catch(NullPointerException exec){
						imgBlock = new ImageIcon("./pics/classic/red.png");
					}
					tabJeuLabel[i][y] = new JLabel(imgBlock, JLabel.CENTER);
					tabJeuLabel[i][y].setPreferredSize(new Dimension(50,50));
					tabJeuLabel[i][y].setOpaque(false);
					panneau2.add(tabJeuLabel[i][y]);
				}
				if(chargerJeu.getTableauJeu()[i][y] == 'V'){
					try{
						if(menuOptionsObs.getChoixTheme() == 1){
							imgBlock = new ImageIcon("./pics/classic/green.png");
						}
						if(menuOptionsObs.getChoixTheme() == 2){
							imgBlock = new ImageIcon("./pics/horror/green.png");
						}
					}catch(NullPointerException exec){
						imgBlock = new ImageIcon("./pics/classic/green.png");
					}
					tabJeuLabel[i][y] = new JLabel(imgBlock, JLabel.CENTER);
					tabJeuLabel[i][y].setPreferredSize(new Dimension(50,50));
					tabJeuLabel[i][y].setOpaque(false);
					panneau2.add(tabJeuLabel[i][y]);
				}
				if(chargerJeu.getTableauJeu()[i][y] == 'B'){
					try{
						if(menuOptionsObs.getChoixTheme() == 1){
							imgBlock = new ImageIcon("./pics/classic/blue.png");
						}
						if(menuOptionsObs.getChoixTheme() == 2){
							imgBlock = new ImageIcon("./pics/horror/blue.png");
						}
					}catch(NullPointerException exec){
						imgBlock = new ImageIcon("./pics/classic/blue.png");
					}
					tabJeuLabel[i][y] = new JLabel(imgBlock, JLabel.CENTER);
					tabJeuLabel[i][y].setPreferredSize(new Dimension(50,50));
					tabJeuLabel[i][y].setOpaque(false);
					panneau2.add(tabJeuLabel[i][y]);
				}
				
			
		}

			
		}
		dejaharger=1;
	}

	/**
	* Méthode qui permet de réactualiser l'affichage des blocs sur la fenêtre du jeu
	* @throws NullPointerException si aucun thème n'a été choisi (On suppose donc que le joueur a choisi le thème "ChorusWorld")
	*/
	public void reactualisation(){
		int i = 0;
		int y = 0;
		for(i=0;i<chargerJeu.getTableauJeu().length;i++){
			for(y=0;y<jeuModel.getTableauGroupe()[i].length;y++){
				if(chargerJeu.getTableauJeu()[i][y] == '.'){
					tabJeuLabel[i][y].setVisible(false);
				}
				if(chargerJeu.getTableauJeu()[i][y] == 'R'){
					try{
						if(menuOptionsObs.getChoixTheme() == 1){
							imgBlock = new ImageIcon("./pics/classic/red.png");
						}
						if(menuOptionsObs.getChoixTheme() == 2){
							imgBlock = new ImageIcon("./pics/horror/red.png");
						}
					}catch(NullPointerException exec){
						imgBlock = new ImageIcon("./pics/classic/red.png");
					}
					tabJeuLabel[i][y].setIcon(imgBlock);
					tabJeuLabel[i][y].setVisible(true);

				}
				if(chargerJeu.getTableauJeu()[i][y] == 'V'){
					try{
						if(menuOptionsObs.getChoixTheme() == 1){
							imgBlock = new ImageIcon("./pics/classic/green.png");
						}
						if(menuOptionsObs.getChoixTheme() == 2){
							imgBlock = new ImageIcon("./pics/horror/green.png");
						}
					}catch(NullPointerException exec){
						imgBlock = new ImageIcon("./pics/classic/green.png");
					}
					tabJeuLabel[i][y].setIcon(imgBlock);
					tabJeuLabel[i][y].setVisible(true);
				}
				if(chargerJeu.getTableauJeu()[i][y] == 'B'){
					try{
						if(menuOptionsObs.getChoixTheme() == 1){
							imgBlock = new ImageIcon("./pics/classic/blue.png");
						}
						if(menuOptionsObs.getChoixTheme() == 2){
							imgBlock = new ImageIcon("./pics/horror/blue.png");
						}
					}catch(NullPointerException exec){
						imgBlock = new ImageIcon("./pics/classic/blue.png");
					}
					tabJeuLabel[i][y].setIcon(imgBlock);
					tabJeuLabel[i][y].setVisible(true);
					
				}
			}		
		}
	}


	/**
	* Méthode (un getter) qui permet d'accèder à la fenetre du jeu (qui a un accès en private). 
	*
	* @return La fenetre du jeu.
	*/
	public JFrame getFenetreJeu(){
		return this.fenetreJeu;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au bouton "Pause" du jeu (qui a un accès en private). 
	*
	* @return Le bouton "Pause" du jeu.
	*/
	public JToggleButton getBoutonPause(){
		return this.boutonPause;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au bouton "Quitter" du jeu (qui a un accès en private). 
	*
	* @return Le boutton "Quitter" du jeu.
	*/
	public JButton getBoutonQuitter(){
		return this.boutonQuitter;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au bouton "Règles" du jeu (qui a un accès en private). 
	*
	* @return Le boutton des "Règles" du jeu.
	*/
	public JButton getBoutonRegles(){
		return this.regles;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au bouton "Triche" du jeu (qui a un accès en private). 
	*
	* @return Le bouton "Triche" du jeu.
	*/
	public JButton getBoutonTricher(){
		return this.triche;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au panneau où sont les blocs du jeu (qui a un accès en private). 
	*
	* @return Le panneau où il y a les blocs du jeu.
	*/	
	public JPanel getPanneau2(){
		return this.panneau2;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au score (JLabel) qui est affiché sur le haut de la fenêtre (qui a un accès en private). 
	*
	* @return Le score (JLabel) qui est affiché sur le haut de la fenêtre.
	*/
	public JLabel getScoreTexte(){
		return this.scoreTexte;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au texte d'encouragement qui est affiché sur le haut de la fenêtre (qui a un accès en private). 
	*
	* @return Le texte d'encouragement qui est affiché sur le haut de la fenêtre.
	*/	
	public JLabel getTexte(){
		return this.texte;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au du menu pause (qui a un accès en private). 
	*
	* @return Le panneau du menu pause.
	*/
	public JPanel getPanneauPause(){
		return this.panneauPause;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au fond du menu pause (qui a un accès en private). 
	*
	* @return Le fond du menu pause.
	*/
	public Image getFondPause(){
		return this.fondPause;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au tableau de JLabel (qui a un accès en private). 
	*
	* @return Le tableau de JLabel.
	*/
	public JLabel[][] getTableauJeuLabel(){
		return this.tabJeuLabel;
	}

}