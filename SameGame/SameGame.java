/**
 * La classe <code>SameGame</code> est la Classe principale d'où le menu principal démmarre. C'est dans cette Classe qu'on retrouve la méthode principale (main) qui lance le jeu (menu principal).
 *  
 * @version 1.1
 * @author Rayan GRIB et Pierre BARBEY
 */

public class SameGame{
	/**
	*La méthode <code>main</code> permet de lancer le menu principal et tout le reste du programme en cascade.
	*/
	public static void main(String[] args){
		//Affichage du message de bienvenue sur la console.
		System.out.println("Bienvenue sur notre SameGame Version " + VERSION + " : Cr\u00e9e par Rayan GRIB et Pierre BARBEY pour le second projet tutor\u00e9 du DUT Informatique \u00e0 Fontainebleau.\n Copyright 2021, Tous droits r\u00e9serv\u00e9s. \n\n En cas de probl\u00e8mes consultez notre documentation.");
		//Instantiation du model du menu principal
		MenuPrincipalModel menuModel = new MenuPrincipalModel();
		//Instantiation de la vue du menu principal
        MenuPrincipal menu = new MenuPrincipal(menuModel);
        //Instantiation du contrôleur du menu principal
		MenuPrincipalObs menuObs = new MenuPrincipalObs(menuModel, menu);
	}
	/**
	* La constante <code>VERSION</code> permet de versionner le jeu.
	*/
	public static final float VERSION = 1.1f;
}