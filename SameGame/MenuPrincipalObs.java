/**
 * La classe <code>MenuPrincipalObs</code> est utilisÃ©e pour choisir les options et aussi lancer une partie. Ici c'est le Contrôlleur, il permet de gérer les actions de l'uitlisateur depuis la Vue et de modifier le Modèle grâce aussi à la Vue. 
 *  
 * @version 1.1
 * @author Rayan GRIB et Pierre BARBEY
 */

//Importation de tout les packages que le Contrôlleur a besoin.

import java.awt.event.*;
import java.io.File;
import java.io.IOException;

public class MenuPrincipalObs implements ActionListener{

    /**
    * Attribut qui contient le Modèle du menu principal (il est initialisé dans le constructeur). 
    */
    private MenuPrincipalModel menuModel;

    /**
    * Attribut qui contient la Vue du menu principal (il est initialisé dans le constructeur). 
    */
    private MenuPrincipal menu;

    /**
    * Attribut qui contient le Modèle du menu d'options. 
    */   
    private OptionsModel menuOptionsModel = new OptionsModel();

    /**
    * Attribut qui contient la Vue du menu d'options (il sera instancié si l'utilisateur clique sur le bouton "Options" du menu principal) 
    */   
    private Options menuOptions;

    /**
    * Attribut qui contient le Contrôlleur du menu d'options (il sera instancié si l'utilisateur clique sur le bouton "Options" du menu principal) 
    */  
    private OptionsObs menuOptionsObs;

    /**
    * Ce constructeur permet de récupérer le Modèle et la Vue du menu principal, d'y avoir accès depuis le Contrôlleur (ici). Ce constructeur est appelé dans la classe <code>SameGame</code>.
    * 
    */
    public MenuPrincipalObs(MenuPrincipalModel menuModel, MenuPrincipal menu){
        this.menuModel = menuModel;
        this.menu = menu;

        //On ajouter les listeners provenant de la Vue

        this.menu.getJouerButton().addActionListener(this);
        this.menu.getOptionsButton().addActionListener(this);
        this.menu.getQuitterButton().addActionListener(this);

        //On affiche le menu

        this.menu.afficherMenu();
    }

    //Ici suivent ce qui sera effectué selon les actions de l'utilisateur.

    /**
    * Cette redéfinition de la méthode actionPerformed de l'Interface <code>ActionListener</code> permet de gèrer les actions de l'utilisateur dans le menu principal notament par le bais de composants graphiques qui sont dans la Vue.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void actionPerformed(ActionEvent evenement){
        //Si l'utilisateur a appuyé sur le bouton "Quitter", on quitte le jeu...
		if(evenement.getSource() == this.menu.getQuitterButton()){
			this.menu.getFenetreMenu().dispose();
			System.exit(0);
		}
        //Si l'utilisateur a appuyé sur le bouton "Jouer", on lance le jeu...
		if(evenement.getSource() == this.menu.getJouerButton()){
    		if(this.menuModel.getOptionOuvert() == true){
    			this.menuOptions.getFenetreOptions().dispose();
    			this.menuModel.setOptionOuvert(false);
    		}
			this.menu.getFenetreMenu().dispose();
            Chargement chargerJeu = new Chargement(menuOptionsObs, menuOptionsModel);
            Jeu jeu = new Jeu(menuOptionsObs, chargerJeu);
            JeuObs jeuObs = new JeuObs(jeu, chargerJeu, menuOptionsObs, menuOptionsModel);
			
		}
        //Si l'utilisateur a appuyé sur le bouton "Options", on ouvre le menu des options...
		if(evenement.getSource() == this.menu.getOptionsButton()){
            this.menuModel.setOptionOuvert(true);
            this.menu.getOptionsButton().setEnabled(false);
            this.menu.getOptionsButton().setText("D\u00e9ja ouvert");
            menuOptions = new Options(menuOptionsModel);
            menuOptionsObs = new OptionsObs(menuOptionsModel, menuOptions, menu, menuModel);
		}

	}
}