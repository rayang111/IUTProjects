/**
 * La classe <code>MenuPrincipalModel</code> est utilisÃ©e pour choisir les options et aussi lancer une partie. Ici c'est le Modèle du menu principal, c'est ici que toutes les données qu'auront besoin la Vue et le Contrôlleur sont gérés.   
 *  
 * @version 1.1
 * @author Rayan GRIB et Pierre BARBEY
 */

//Importation de tout les packages que le Modèle aura besoin

import java.io.File;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import java.io.IOException;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;

public class MenuPrincipalModel{

	/**
	* Attribut qui permet de savoir si le menu des options a été ouvert ou non. 
	*/
	private boolean optionOuvert = false;

	/**
	* Attribut qui contient des phrases qui sont affichées sur la fenêtre du menu principal
	*/
	private String[] phrases = {" La vie est difficile mais une bonne partie de SameGame l'adoucie... ", 
		" Nous esp\u00e9rons avoir une bonne note grâce à ce jeu ! ",
		" Vive l'APL ! ", " Java est un tr\u00e8s bon langage de programmation orient\u00e9 objet. ", 
		" Une partie de SameGame ne sera jamais la même... "};

	/**
	* Méthode (un getter) qui permet d'accèder aux phrases qui s'affichent dans le menu principal (qui a un accès en private). 
	*
	* @return Les phrases du Modèle du menu principal.
	*/
	public String[] getPhrases(){
		return this.phrases;
	}

	/**
	* Méthode (un getter) qui permet d'accèder à l'attribut qui permet de savoir si le menu options à été ouvert ou pas (qui a un accès en private). 
	*
	* @return La valeur (boolean) de l'atribut optionOuvert.
	*/
	public boolean getOptionOuvert(){
		return this.optionOuvert;
	}

	/**
	* Méthode (un setter) qui permet de modifier/mettre à jour l'attribut qui permet de savoir si le menu options à été ouvert ou pas (qui a un accès en private). 
	*
	* @param etat L'état qu'on souhaite mettre (true ou false).
	*/
	public void setOptionOuvert(boolean etat){
		this.optionOuvert = etat;
	}
}