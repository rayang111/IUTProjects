/**
 * La classe <code>FinModel</code> est utilisÃ©e pour gérer les données du menu Fin, Ici c'est le Modèle du menu Fin.
 *  
 * @version 1.1
 * @author Rayan GRIB et Pierre BARBEY
 */
public class FinModel{

	/**
	* Attribut qui permet de savoir si on a battu le meilleur score ou non
	*/
	private boolean scoreSuperieur;

	/**
	* Méthode (un getter) qui permet d'accèder à l'état de scoreSuperieur (qui a un accès en private). 
	*
	* @return Si le meilleur score a été battu ou non (true ou false)
	*/
	public boolean getScoreSuperieur(){
		return this.scoreSuperieur;
	}

	/**
	* Méthode (un setter) qui permet de modifier l'état de scoreSuperieur (qui a un accès en private). 
	*
	* @param etat true ou false (vrai ou faux)
	*/
	public void setScoreSuperieur(boolean etat){
		this.scoreSuperieur = etat;
	}

}