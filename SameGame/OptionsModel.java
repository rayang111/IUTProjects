/**
 * La classe <code>OptionsModel</code> est utilisÃ©e gerer les parrametres du jeu et notament sur le type de niveau souhaitee. Ici c'est le Modèle du menu d'options, c'est ici que toutes les données qu'auront besoin la Vue et le Contrôlleur sont gérés.   
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
import javax.swing.*;
import java.awt.*;

public class OptionsModel{

	/**
	*  Atribut qui contient les choix des thèmes.
	*/
	private String[] choixBox = {"ChorusWorld (Classic)","Horrorcore"};

	/**
	*  Atribut qui permet de savoir si on a choisi de choisir un fichier ou non.
	*/
	private boolean choixFichierChoisi = false;

	/**
	*  Atribut qui permet de savoir si on a choisi de générer de l'aléatoire ou non.
	*/
	private boolean choixFichierAlea = false;
	
	/**
	*  Atribut qui permet de savoir si on a activé le mode triche ou non.
	*/
	private boolean choixAutoriserTriche = false;
	
	/**
	*  Atribut qui permet de choisir un fichier si on a choisi de choisir un fichier.
	*/
	private JFileChooser path = new JFileChooser("./levels/");


	/**
	* Méthode (un getter) qui permet d'accèder aux choix sur les thèmes (qui a un accès en private). 
	*
	* @return Le tableau de String sur les choix des thèmes.
	*/
	public String[] getChoixBox(){
		return this.choixBox;
	}

	/**
	* Méthode (un getter) qui permet d'accèder à l'atribut qui permet de savoir si on a choisi de choisir un fichier (qui a un accès en private). 
	*
	* @return L'atribut qui permet de savoir si on a choisi de choisir un fichier.
	*/
	public boolean getChoixFichierChoisi(){
		return this.choixFichierChoisi;
	}

	/**
	* Méthode (un getter) qui permet d'accèder à l'atribut qui permet de savoir si on a choisi de générer le niveau aléatoirement (qui a un accès en private). 
	*
	* @return L'atribut qui permet de savoir si on a choisi de générer le niveau aléatoirement.
	*/
	public boolean getChoixFichierAlea(){
		return this.choixFichierAlea;
	}

	/**
	* Méthode (un setter) qui permet de modifier l'atribut qui permet de savoir si on a choisi de générer le niveau aléatoirement (qui a un accès en private). 
	*
	* @param etat L'état que l'on veut mettre (true ou false).
	*/
	public void setChoixFichierAlea(boolean etat){
		this.choixFichierAlea = etat;
	}

	/**
	* Méthode (un setter) qui permet de modifier l'atribut qui permet de savoir si on a choisi de choisir un fichier (qui a un accès en private). 
	*
	* @param etat L'état que l'on veut mettre (true ou false).
	*/
	public void setChoixFichierChoisi(boolean etat){
		this.choixFichierChoisi = etat;
	}

	/**
	* Méthode (un getter) qui permet d'accèder à l'atribut qui permet de savoir si on a activé le mode triche (qui a un accès en private). 
	*
	* @return L'atribut qui permet de savoir si on a activé le mode triche.
	*/
	public boolean getChoixAutoriserTriche(){
		return this.choixAutoriserTriche;
	}

	/**
	* Méthode (un setter) qui permet de modifier l'atribut qui permet de savoir si on a activé le mode triche (qui a un accès en private). 
	*
	* @param etat L'état que l'on veut mettre (true ou false).
	*/
	public void setChoixAutoriserTriche(boolean etat){
		this.choixAutoriserTriche = etat;
	}

	/**
	* Méthode (un getter) qui permet d'accèder à l'atribut qui permet de choisir un fichier (qui a un accès en private). 
	*
	* @return L'atribut qui permet de de choisir un fichier.
	*/
	public JFileChooser getPath(){
		return this.path;
	}

	/**
	* Méthode (un getter) qui permet de savoir si a choisi ou non de choisir un fichier. 
	*
	* @return 1 si on a choisi de choisir un fichier, 0 si on a pas choisi de choisir un fichier.
	*/
	public int getChoice(){
		if(choixFichierChoisi){
			return 1;
		}else{
			return 0;
		}
	}
}