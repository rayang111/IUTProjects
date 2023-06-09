package fr.iutfbleau.projetIHM2021FI2.MNP;
import fr.iutfbleau.projetIHM2021FI2.API.*;

import java.awt.*;

/**
* La classe permtant de lancer le programme (contient le main) qui instencie le premier modèle qui est la classe permetant de gérer les bases de données, la vue et le controlleur
*
*/
public class Booking{
	/**
	* @param args arguments issues du terminal où le programme est lancé (Type String[]).
	* La méthode "main" qui est la méthode où on lance le programme.
	* @throws Exception Cette erreur arrive lorsque il y a un problème pour trouver les classes du logiciel.
	*
	*/
	 public static void main(String[] args) {
	 	try{
	 	BaseDonnee model = new BaseDonnee();
	 	Graphique vue = new Graphique(model);
	 	Controlleur controlleur = new Controlleur(vue, model);
	 	System.out.printf("Bienvenue sur Booking\n");
	 	} catch(Exception e1){
	 		System.err.println("Erreur los du lancement du logiciel, vous devrez sans doute réinstaller le logiciel.\n" +e1);
	 	}
	 }
}