/**
 * La classe <code>Chargement</code> est utilisÃ©e pour charger une partie du jeu.
 *  
 * @version 1.1
 * @author Rayan GRIB et Pierre BARBEY
 */

//Importation des packages que Chargement a besoin

import java.util.Random;
import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.FileNotFoundException;
import javax.swing.JOptionPane;
import java.util.Arrays;

public class Chargement{

	/**
	*	Attribut qui contient la grille du jeu qui contient les blocs
	*/
	private char[][] tab_jeu = new char[10][15];

	/**
	*	Attribut qui contient les caractèrres les carractères compatibles
	*/
	private char[] rvb = {'R','V','B'}; 

	/**
	*	Attribut qui contient les coordonnées en x
	*/
	private int i = 0;


	/**
	*	Attribut qui contient les coordonnées en y
	*/
	private int y = 0;

	/**
	*	Attribut qui contient le fichier choisi qui va être lu.
	*/
	private File fichier;

	/**
	*	Attribut qui contient le buffer qui permet de lire le fichier choisi.
	*/
	private BufferedReader lecteurAvecBuffer = null;

	/**
	*	Attribut qui contient une référence à la classe jeu (Modèle). (il sera instancié dans le constructeur).
	*/
	private Jeu jeu;

	/**
	*	Attribut qui contient une référence à la classe Options (Contrôlleur). (il sera instancié dans le constructeur).
	*/
	private OptionsObs menuOptionsObs;

	/**
	*	Attribut qui contient une référence à la classe Options (Modèle). (il sera instancié dans le constructeur).
	*/
	private OptionsModel menuOptionsModel;

	/**
	* Ce constructeur permet de récupérer le Modèle d'<code>OptionsModel</code> et aussi le Contrôlleur de <code>OptionsObs</code>, d'y avoir accès depuis <code>Chargement</code> (ici). Ce constructeur est appelé dans la classe <code>JeuObs</code>.
	* 
	*/
	public Chargement( OptionsObs menuOptionsObs, OptionsModel menuOptionsModel){
		this.jeu = jeu;
		this.menuOptionsObs = menuOptionsObs;
		this.menuOptionsModel = menuOptionsModel;
	}

	/**
	* Cette Méthode permet de charger une une grille avec la gestion d'erreurs. Cette Méthode appelle automatique la méthode setTab()
	* @throws IOException Si une erreur de lecture apparaît
	* @throws NullPointerException Si aucun fichier n'a été sélectionné
	*/
	public void chargerPartie(){
		try{
			this.setTab();	
		}
		catch(IOException exc){
			JOptionPane.showMessageDialog(null, "Erreur lors du chargement du jeu...\n"+exc.getMessage()+"\n\nSortie du jeu...", "Erreur", JOptionPane.ERROR_MESSAGE);
			System.err.println("Erreur lors du chargement du jeu...  IOException");
			System.exit(0);
		}
		catch(NullPointerException exc){
			JOptionPane.showMessageDialog(null, "Erreur lors de l'ouverture du fichier\n\nAucun fichier de niveau n'a été sélectionné alors que vous avez choisir d'ouvrir un niveau, Veuliez en choisir un\n\nSortie du jeu...", "Erreur", JOptionPane.ERROR_MESSAGE);
			System.err.println("Erreur lors de l'ouverture du fichier" + menuOptionsModel.getPath().getName(fichier) + " NullPointerException");
			System.exit(0);		
		}

	}

	/**
	* Cette Méthode permet de charger une une grille.
	* @throws IOException Si le fichier choisi a des carractères non compatables (en dehors de R, V, B) ou/et la taille est supérieur ou inférieur à 15x10.
	* @throws FileNotFoundException Si aucun fichier introuvable
	*/
	public void setTab() throws IOException{
		//Si on a choisi de faire l'aléatoire
		if (menuOptionsModel.getChoice() == 0) {
			for(i = 0; i < tab_jeu.length; i++){
				for (y=0; y < tab_jeu[i].length ; y++ ){
					tab_jeu[i][y] = rvb[new Random().nextInt(3)];
				}
			}
		}
		//Si on a choisi de lire dans un fichier
		if(menuOptionsModel.getChoice() == 1){
			//On récupere le fichier choisi sur le JFileChooser
			fichier = menuOptionsModel.getPath().getSelectedFile();
			//On lit dans le fichier
			if(fichier.canRead()){
				String ligne;
				try{
					lecteurAvecBuffer = new BufferedReader(new FileReader(fichier));
				}
				catch(FileNotFoundException exc){
					JOptionPane.showMessageDialog(null, "Erreur lors de l'ouverture du fichier\n\nLe fichier est introuvable...", 
					"Erreur", JOptionPane.ERROR_MESSAGE);
					System.err.println("Erreur lors de l'ouverture du fichier sélectionné FileNotFoundException");
					System.exit(0);	
				}
				i = 0;
				//On lit jusqu'à que on atteinne la fin du fichier et que on dépasse la longeur de grille en hauteur
				while((ligne = lecteurAvecBuffer.readLine()) != null && i < tab_jeu.length){
					char[] ligneChar = ligne.toCharArray();
					for(y = 0; y<ligneChar.length && y<tab_jeu[i].length;y++){
						if(ligneChar[y] != 'R' && ligneChar[y] != 'V' && ligneChar[y] != 'B'){
							IOException erreurFichierInvalide = new IOException("Ce fichier contient des carracteres non valides.\n\nRappel : votre fichier doit contenir que ces carracteres : R, V, B ");
							throw erreurFichierInvalide;
						}
						if(ligneChar.length != tab_jeu[i].length){
							IOException erreurTailleInvalide = new IOException("Ce fichier a une taille qui n'est pas egale a 15x10.\n\n Veuliez modifier votre fichier ou ouvrir un autre.");
							throw erreurTailleInvalide;
						}
						tab_jeu[i][y] = ligneChar[y];
					}
					i = i + 1;
				}
				//on ferme le fichier
				lecteurAvecBuffer.close();
			}
		}
	}

	/**
	*	Méthode qui permet d'afficher la grille sur la console.
	*/
	public void getTab(){
		System.out.println("DEBUT TABLEAU");
		for(i = 0; i < tab_jeu.length; i++){
			for (y=0; y < tab_jeu[i].length ; y++ ){
				System.out.print(tab_jeu[i][y]);
			}
			System.out.println("");
		}
		System.out.println("FIN TABLEAU");
	}

	/**
	*	Méthode qui permet de réinisialiser la grille à des carractères '\0'.
	*/
	public void renisialiser(){
		for(i = 0; i < tab_jeu.length; i++){
			for (y=0; y < tab_jeu[i].length ; y++ ){
				tab_jeu[i][y] = '\0';
			}
		}
	}

	/**
	* Méthode (un getter) qui permet d'accèder au buffer qui lit le fichier choisi (qui a un accès en private). 
	*
	* @return Le buffer qui lit le fichier choisi.
	*/
	public BufferedReader getLecteur(){
		return this.lecteurAvecBuffer;
	}

	/**
	* Méthode (un getter) qui permet d'accèder à la grille du jeu (qui a un accès en private). 
	*
	* @return La grille du jeu.
	*/
	public char[][] getTableauJeu(){
		return this.tab_jeu;
	} 

	/**
	* Méthode (un getter) qui permet d'accèder carractères compatibles (qui a un accès en private). 
	*
	* @return Un tableau avec les carractères compatibles.
	*/
	public char[] getRVB(){
		return this.rvb;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au fichier qui a été choisi (qui a un accès en private). 
	*
	* @return Le fichier choisi.
	*/
	public File getFichier(){
		return this.fichier;
	}



}
