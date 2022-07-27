/**
 * La classe <code>JeuObs</code> est utilisÃ©e pour gerer une partie en cours et sa fin. Cette Classe fait partie de la Classe Jeu, c'est à dire, JeuVue (Vue), JeuObs (Controlleur) et cette Classe qui est le Model. C'est ici où on gère les données d'une partie. Elle comunique avec le Controlleur (JeuObs).
 *  
 * @version 1.1
 * @author Rayan GRIB
 * @author Pierre BARBEY
 */
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class JeuObs implements ActionListener, ItemListener, WindowListener{

	/**
    * Attribut qui appel la classe Jeu. 
    */
	private Jeu jeuModel;
	/**
    * Attribut qui appel la classe Affichage. 
    */
	private Affichage afficher;
	/**
    * Attribut qui appel la classe Chargement. 
    */
	private Chargement chargerJeu;
	/**
    * Attribut qui appel la classe OptionObs. 
    */
	private OptionsObs menuOptionsObs;
	/**
    * Attribut qui appel la classe OptionModel. 
    */
	private OptionsModel menuOptionsModel;
	/**
    * Attribut qui appel au constructeur ReglesModel. 
    */
	private ReglesModel reglesModel = new ReglesModel();
	/**
    * Attribut qui appel la classe Regles. 
    */
	private Regles regles;
	/**
    * Attribut qui appel la classe ReglesObs. 
    */
	private ReglesObs reglesObs;

	/**
    *  Ce constructeur est appelé dans la classe <code>Jeu</code>.
	*  @param jeuModel fait appel la classe Jeu
	*  @param chargerJeu fait appel la classe Chargement
	*  @param menuOptionsObs fait appel la classe OptionsObs
	*  @param menuOptionsModel fait appel la classe OptionsModel
    */
	public JeuObs(Jeu jeuModel,Chargement chargerJeu, OptionsObs menuOptionsObs, OptionsModel menuOptionsModel){
		this.jeuModel = jeuModel;
		this.afficher = afficher;
		this.chargerJeu = chargerJeu;
		this.menuOptionsObs = menuOptionsObs;
		this.menuOptionsModel = menuOptionsModel;
		this.afficher = new Affichage(jeuModel, chargerJeu, menuOptionsModel, menuOptionsObs);

		this.afficher.getBoutonQuitter().addActionListener(this);
		this.afficher.getBoutonPause().addItemListener(this);
		this.afficher.getBoutonTricher().addActionListener(this);
		this.afficher.getFenetreJeu().addWindowListener(this);
		this.afficher.getBoutonRegles().addActionListener(this);

		this.chargerJeu.chargerPartie();
		this.chargerJeu.getTab();
		this.afficher.afficher();
		this.subrillance();
		this.jeuModel.jeu();
		this.jeuModel.nbGroup();
		this.jeuModel.meilleurScoreLecture();
		this.chargerJeu.getTab();
	}

	/**
	* Méthode qui quite le menu pause. 
	*/
	public void pauseExit(){
		afficher.getScoreTexte().setBackground(new Color(65,105,225));
		afficher.getPanneauPause().setVisible(false);
		afficher.getPanneau2().setVisible(true);
		afficher.getFenetreJeu().setResizable(true);
		afficher.getBoutonPause().setText("Pause");
		try{
			if(menuOptionsObs.getChoixTheme() == 1){
				afficher.getTexte().setText(" Bon courage ! Détruisez les cubes. ");
			}
			if(menuOptionsObs.getChoixTheme() == 2){
				afficher.getTexte().setText(" ARGHHHHHHHH ! Pulvérisez tout... ");
			}
		}catch(NullPointerException exec){
			afficher.getTexte().setText(" Bon courage ! Détruisez les cubes. ");
		}
    	jeuModel.setIsPaused(false);
	}

	/**
	* Méthode qui affiche le menu pause. 
	*/
	public void pauseEnter(){
		jeuModel.setIsPaused(true);
		afficher.getScoreTexte().setBackground(Color.DARK_GRAY);
		afficher.getPanneau2().setVisible(false);
		afficher.getPanneauPause().setVisible(true);
		afficher.getFenetreJeu().setResizable(false);
		afficher.getBoutonPause().setText("Reprendre");
		afficher.getTexte().setText("Jeu en Pause... ");
	}

	/**
	* Méthode qui permet d'ajouter les MouseListener sur les blocs pour qu'ils puissent être intéractifs (une surbrillance est rajoutée depuis <code>Observateur</code>, sa couleur diffère selon thème choisi)
	* 
	*/
	public void subrillance(){
		int i=0;
		int j=0;
		for(i=0;i<10;i++){
			for(j=0;j<15;j++){
				afficher.getTableauJeuLabel()[i][j].addMouseListener(new Observateur(afficher.getTableauJeuLabel(), i, j, afficher, chargerJeu, jeuModel, menuOptionsObs, this));
			}
		}
	}

	/**
	* Méthode qui permet de "détruire" un bloc, du moins surtout un groupe de blocs (il est utilisé plus précisément dans <code>Observateur</code>).
	* 
	*/
	public void detruire(int k,int l){
		jeuModel.getTableauGroupe()[k][l] = false;		
	}

	/**
    * Cette redéfinition de la méthode actionPerformed de l'Interface <code>ActionListener</code> permet de gèrer les actions de l'utilisateur dans le menu principal notament par le bais de composants graphiques qui sont dans la Vue.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void actionPerformed(ActionEvent evenement){
		if(evenement.getSource() == afficher.getBoutonQuitter()){
			int question = JOptionPane.showConfirmDialog(afficher.getFenetreJeu(), "Voulez-vous vraiment quitter votre partie ? Tout ce que vous aurez fait ne sera pas sauvgardee.", "Quitter ?", JOptionPane.YES_NO_OPTION);
			if(question == JOptionPane.YES_OPTION){
				jeuModel.setQuitter(true);
				if(jeuModel.getIsPaused() == true){
					pauseExit();
					afficher.getBoutonPause().setSelected(false);
					jeuModel.setIsPaused(false);
				}
				afficher.getFenetreJeu().dispose();
				chargerJeu.renisialiser();
				System.exit(0);
			}
		}
		if(evenement.getSource() == afficher.getBoutonTricher()){
			jeuModel.setScore(9999999);
			jeuModel.setQuitter(true);
			FinModel finModel = new FinModel();
			Fin fin = new Fin(finModel, jeuModel);
			FinObs finObs = new FinObs(fin, finModel, afficher, jeuModel, menuOptionsObs);
		}
		if(evenement.getSource() == afficher.getBoutonRegles()){
			regles = new Regles(reglesModel, afficher);
			reglesObs = new ReglesObs(reglesModel, regles);
		}	
	}

	 /**
    * Cette redéfinition de la méthode itemStateChanged de l'Interface <code>ItemListener</code> permet de tester si un item a été sélectionné.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void itemStateChanged(ItemEvent evenement){
		if(evenement.getSource() == afficher.getBoutonPause() && afficher.getBoutonPause().isSelected()){
			pauseEnter();

		}
		if(evenement.getSource() == afficher.getBoutonPause() && !afficher.getBoutonPause().isSelected()){
			pauseExit();
		}	
	}

	/**
    * Cette redéfinition de la méthode windowOpened de l'Interface <code>WindowListener</code> permet de gèrer les actions de l'utilisateur dans le menu d'options notament par le bais de la fenêtre du menu.
    * Ici c'est qui sera effectué si une fenêtre a été ouverte.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void windowOpened(WindowEvent evenement){


	}

	/**
    * Cette redéfinition de la méthode windowClosed de l'Interface <code>WindowListener</code> permet de gèrer les actions de l'utilisateur dans le menu d'options notament par le bais de la fenêtre du menu.
    * Ici c'est qui sera effectué si une fenêtre a été fermée.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void windowClosed(WindowEvent evenement){


	}

	 /**
    * Cette redéfinition de la méthode windowActivated de l'Interface <code>WindowListener</code> permet de gèrer les actions de l'utilisateur dans le menu d'options notament par le bais de la fenêtre du menu.
    * Ici c'est qui sera effectué si une fenêtre a été mise en focus.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void windowActivated(WindowEvent evenement){
		if(!afficher.getBoutonPause().isSelected() && jeuModel.getQuitter() == false && jeuModel.getIsPaused() == true){
			pauseExit();
		}
	}
	

	 /**
    * Cette redéfinition de la méthode windowClosing de l'Interface <code>WindowListener</code> permet de gèrer les actions de l'utilisateur dans le menu d'options notament par le bais de la fenêtre du menu.
    * Ici c'est qui sera effectué si une fenêtre est en train de fermer.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void windowClosing(WindowEvent evenement){

	}
	

	/**
    * Cette redéfinition de la méthode windowDeactivated de l'Interface <code>WindowListener</code> permet de gèrer les actions de l'utilisateur dans le menu d'options notament par le bais de la fenêtre du menu.
    * Ici c'est qui sera effectué si une fenêtre n'est plus en focus.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void windowDeactivated(WindowEvent evenement){
		if(jeuModel.getQuitter() == false && jeuModel.getIsPaused() == false){
			pauseEnter();
		}
	}
	

	/**
    * Cette redéfinition de la méthode windowDeiconified de l'Interface <code>WindowListener</code> permet de gèrer les actions de l'utilisateur dans le menu d'options notament par le bais de la fenêtre du menu.
    * Ici c'est qui sera effectué si une fenêtre a été réduite.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void windowDeiconified(WindowEvent evenement){

	}


	 /**
    * Cette redéfinition de la méthode windowIconified de l'Interface <code>WindowListener</code> permet de gèrer les actions de l'utilisateur dans le menu d'options notament par le bais de la fenêtre du menu.
    * Ici c'est qui sera effectué si une fenêtre a été restaurée.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void windowIconified(WindowEvent evenement){

	}

   }
