/**
 * La classe <code>OptionsObs</code> est utilisÃ©e gerer les parrametres du jeu et notament sur le type de niveau souhaitee. Ici c'est le Contrôlleur, il permet de gérer les actions de l'uitlisateur depuis la Vue et de modifier le Modèle grâce aussi à la Vue. 
 *  
 * @version 1.1
 * @author Rayan GRIB et Pierre BARBEY
 */

//Importation du package que le Contrôlleur a besoin.

import java.awt.event.*;



public class OptionsObs implements ActionListener, WindowListener, ItemListener{

	/**
	* Atribut qui contient le Modèle du menu d'options pour y avoir accès depuis le contrôlleur (L'atribut est initialisé dans constructeur).
	*/
	private OptionsModel menuOptionsModel;

	/**
	* Atribut qui contient la Vue du menu d'options pour y avoir accès depuis le contrôlleur (L'atribut est initialisé dans constructeur).
	*/
	private Options menuOptions;

	/**
	* Atribut qui contient la Vue du menu principal pour y avoir accès depuis le contrôlleur (L'atribut est initialisé dans constructeur).
	*/
	private MenuPrincipal menu;

	/**
	* Atribut qui contient le Modèle du menu principal pour y avoir accès depuis le contrôlleur (L'atribut est initialisé dans constructeur).
	*/
	private MenuPrincipalModel menuModel;

    /**
    * Ce constructeur permet de récupérer le Modèle et la Vue du menu d'options, mais aussi ceux du menu principal (pour effectuer certaines tâches), d'y avoir accès depuis le Contrôlleur (ici). Ce constructeur est appelé dans la classe <code>MenuPrincipalObs</code>.
    * 
    */
	public OptionsObs(OptionsModel menuOptionsModel, Options menuOptions, MenuPrincipal menu, MenuPrincipalModel menuModel){
		this.menuOptionsModel = menuOptionsModel;
		this.menuOptions = menuOptions;
		this.menu = menu;
		this.menuModel = menuModel;

		//On ajouter les listeners provenant de la Vue

		this.menuOptions.getOptionsFermer().addActionListener(this);
		this.menuOptions.getChoixFichier().addItemListener(this);
		this.menuOptions.getChoixAlea().addItemListener(this);
		this.menuOptions.getAutoriserTriche().addItemListener(this);
		this.menuOptions.getChoisir().addActionListener(this);
		this.menuOptions.getFenetreOptions().addWindowListener(this);

		//On affiche le menu

		this.menuOptions.afficherOptions();
	}

	/**
	* Méthode qui permet savoir quel thème a été choisi.
	* @return 1 si le thème est "ChorusWorld", 2 si le thème est "Horrorcore", 0 si aucun thème n'a été choisi (ce qui sera jamais le cas car par défaut c'est "ChorusWorld" qui est choisi).
	*/
	public int getChoixTheme(){
		if(this.menuOptions.getChoixTheme().getSelectedItem() == menuOptionsModel.getChoixBox()[0]){
			return 1;
		}
		if(this.menuOptions.getChoixTheme().getSelectedItem() == menuOptionsModel.getChoixBox()[1]){
			return 2;
		}else{
			return 0;
		}
	}

    /**
    * Cette redéfinition de la méthode actionPerformed de l'Interface <code>ActionListener</code> permet de gèrer les actions de l'utilisateur dans le menu d'options notament par le bais de composants graphiques qui sont dans la Vue.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void actionPerformed(ActionEvent evenement){
		//Si l'utilisateur a appuyé sur le bouton "Fermer"
		if(evenement.getSource() == this.menuOptions.getOptionsFermer()){
			this.menuOptions.getFenetreOptions().dispose();
			this.menuModel.setOptionOuvert(false);
		}
		//Si l'utilisateur a appuyé sur le bouton "Choisir un fichier"
		if(evenement.getSource() == this.menuOptions.getChoisir()){
			this.menuOptions.choixFichier();
		}
	}

    /**
    * Cette redéfinition de la méthode windowOpened de l'Interface <code>WindowListener</code> permet de gèrer les actions de l'utilisateur dans le menu d'options notament par le bais de la fenêtre du menu.
    * Ici c'est qui sera effectué si une fenêtre a été ouverte.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void windowOpened(WindowEvent evenement){
		this.menu.getOptionsButton().setEnabled(false);
		this.menuOptions.getChoisir().setEnabled(false);
		this.menu.getOptionsButton().setText("D\u00e9ja ouvert");

	}

    /**
    * Cette redéfinition de la méthode windowClosed de l'Interface <code>WindowListener</code> permet de gèrer les actions de l'utilisateur dans le menu d'options notament par le bais de la fenêtre du menu.
    * Ici c'est qui sera effectué si une fenêtre a été fermée.
    * @param evenement L'évenement produit par l'utilisateur. 
    */	
	@Override
	public void windowClosed(WindowEvent evenement){
		this.menu.getOptionsButton().setEnabled(true);
		this.menu.getOptionsButton().setText("Options");

	}

    /**
    * Cette redéfinition de la méthode windowActivated de l'Interface <code>WindowListener</code> permet de gèrer les actions de l'utilisateur dans le menu d'options notament par le bais de la fenêtre du menu.
    * Ici c'est qui sera effectué si une fenêtre a été mise en focus.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void windowActivated(WindowEvent evenement){

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

    /**
    * Cette redéfinition de la méthode itemStateChanged de l'Interface <code>ItemListener</code> permet de gèrer les actions de l'utilisateur dans le menu d'options notament par le bais de composants graphiques qui sont dans la Vue, qui ont des états (sélectionné/désélectionné).
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void itemStateChanged(ItemEvent evenement){
		//Si l'utilisateur a sélectionné sur le bouton radio "Jouer un niveau depuis un fichier" et que le bouton radio "Jouer un niveau généré aléatoirement" est sélectionné
		if(evenement.getSource() == this.menuOptions.getChoixFichier() && this.menuOptionsModel.getChoixFichierChoisi() == false){
			this.menuOptionsModel.setChoixFichierChoisi(true);
			this.menuOptionsModel.setChoixFichierAlea(false);
			this.menuOptions.getChoisir().setEnabled(true);
		}
		//Si l'utilisateur a sélectionné sur le bouton radio "Jouer un niveau généré aléatoirement" et que le bouton radio "Jouer un niveau depuis un fichier" est est sélectionné
		if(evenement.getSource() == this.menuOptions.getChoixAlea() && this.menuOptionsModel.getChoixFichierChoisi() == true){
			this.menuOptionsModel.setChoixFichierAlea(true);
			this.menuOptions.getChoisir().setEnabled(false);
			this.menuOptions.getMenuOptionsModel().setChoixFichierChoisi(false);
		}
		//Si l'utilisateur a sélectionné sur le bouton radio "Jouer un niveau depuis un fichier" et que ce bouton est sélectionné
		if(evenement.getSource() == this.menuOptions.getChoixFichier() && this.menuOptionsModel.getChoixFichierChoisi() == true){
			this.menuOptionsModel.setChoixFichierChoisi(true);
			this.menuOptionsModel.setChoixFichierAlea(false);
			this.menuOptions.getChoisir().setEnabled(true);
		}
		//Si l'utilisateur a sélectioné la case à cocher mode de tricher et que cette dernière était délectionnée
		if(evenement.getSource() == this.menuOptions.getAutoriserTriche() && evenement.getStateChange() == ItemEvent.SELECTED){
			this.menuOptionsModel.setChoixAutoriserTriche(true);
			System.out.println(menuOptionsModel.getChoixAutoriserTriche());
		}
		//Si l'utilisateur a sélectioné la case à cocher mode de tricher et que cette dernière était sélectionnée
		if(evenement.getSource() == this.menuOptions.getAutoriserTriche() && evenement.getStateChange() == ItemEvent.DESELECTED){
			this.menuOptionsModel.setChoixAutoriserTriche(false);
			System.out.println(this.menuOptionsModel.getChoixAutoriserTriche());
		}
	} 


}