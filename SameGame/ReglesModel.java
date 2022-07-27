import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.*;

public class ReglesModel{

	/**
    * Attribut qui recupère le texte des regles dans le fichier. 
    */
	private String texteComplet = "";
	/**
    * Attribut qui représente le flux. 
    */
	private BufferedReader flux;

	/**
	* La méthode ouvre le fichier règle et recupère les règles. 
	*
	*/
	public void ouvertureFichier(){
		try{
			flux = new BufferedReader(new InputStreamReader(new FileInputStream("./regles.txt"), "UTF-8"));
			try{
				String texteRecup;
				while((texteRecup = flux.readLine()) != null){
					texteComplet = texteComplet +"\n"+ texteRecup;
				}
			}catch(IOException e) {
        		System.err.println("Erreur de lecture dans le fichier regles.txt !");
			}
		}catch(IOException e) {
     		System.err.println("Impossible d'ouvrir le fichier regles.txt en lecture ! Il doit être dans le répertoire du jeu.");
    	}
	}

	/**
	* Méthode (un getter) qui permet d'accèder à l'attribut qui recupère le texte des regles dans le fichier (qui a un accès en private). 
	*
	* @return le texte des regles.
	*/
	public String getTexteComplet(){
		return this.texteComplet;
	}

	/**
	* Méthode (un setter) qui permet de modifier l'atribut qui recupère le texte des regles dans le fichier (qui a un accès en private). 
	*
	* @param etat le texte des regles.
	*/
	public void setTexteComplet(String texte){
		this.texteComplet = texte;
	}

	/**
	* Méthode (un getter) qui permet d'accèder à l'attribut qui représente le flux (qui a un accès en private). 
	*
	* @return le flux.
	*/
	public BufferedReader getFlux(){
		return this.flux;
	}
}