import javax.swing.*;
import java.awt.event.*;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import java.io.IOException;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;
import java.io.File;
import java.io.*;

public class FinObs implements ActionListener{

	/**
    * Attribut qui appel la classe Fin. 
    */
	private Fin fin;
	/**
    * Attribut qui appel la classe FinModel. 
    */
	private FinModel finModel;
	/**
    * Attribut qui appel la classe Affichage. 
    */
	private Affichage afficher;
	/**
    * Attribut qui appel la classe Jeu. 
    */
	private Jeu jeu;
	/**
    * Attribut qui appel la classe OptionsObs. 
    */
	private OptionsObs menuOptionsObs;

	/**
    *  Ce constructeur est appelé dans la classe <code>Observateur</code><code>JeuObs</code>.
    *  @param fin Attribut qui appel la classe Fin.
    *  @param finModel Attribut qui appel la classe FinModel.
	*  @param afficher Attribut qui appel la classe Affichage.
	*  @param jeu fAttribut qui appel la classe Jeu. 
	*  @param menuOptionsObs Attribut qui appel la classe OptionsObs.
    */
	public FinObs(Fin fin, FinModel finModel, Affichage afficher, Jeu jeu, OptionsObs menuOptionsObs){
		this.fin = fin;
		this.finModel = finModel;
		this.afficher = afficher;
		this.jeu = jeu;
		this.menuOptionsObs = menuOptionsObs;

		this.fin.getBoutonQuiterFin().addActionListener(this);

		this.gagnee();
		this.meilleurScoreEcriture();
		this.fin.afficherFin();
	}

	/**
	* Méthode qui permet de changer les variable afin d'indiquer la fin du jeu 
	*/
	public void executerFin(){
		fin.getFenetreFin().setTitle("Victoire !");
		fin.setImageEtatFin(new ImageIcon("./pics/gagne.gif"));
		try{
			if(menuOptionsObs.getChoixTheme() == 1){
				fin.setImageFin(new ImageIcon("./pics/victoire.gif"));
			}
			if(menuOptionsObs.getChoixTheme() == 2){
				fin.setImageFin(new ImageIcon("./pics/hg.gif"));
			}
		}catch(NullPointerException exec){
			fin.setImageFin(new ImageIcon("./pics/victoire.gif"));
		}
		fin.getVictoire_texte().setText("Vous avez gagné !");
	}

	/**
	* Méthode qui d'écrir le meilleur score dans un fichier. 
	*/
	public void meilleurScoreEcriture(){
		File fichierMeilleurScore = new File("./meilleurScore.bin");
		try{
			FileOutputStream streamMeilleurScore = new FileOutputStream(fichierMeilleurScore);
    		DataOutputStream flux = new DataOutputStream(streamMeilleurScore);
			try{
				if(jeu.getMeilleurScore() < jeu.getScore()){
					jeu.setMeilleurScore(jeu.getScore());
					flux.writeInt(jeu.getScore());
					finModel.setScoreSuperieur(true);
				} else{
					flux.writeInt(jeu.getMeilleurScore());
				}
			}catch(IOException exec){
				System.err.println("Erreur d'écriture dans le fichier meilleurScore.bin...");
			}
			try{
				flux.close();
			}catch(IOException exec){
				System.err.println("Erreur lors de la fermeture en écriture du fichier meilleurScore.bin...");
			}
		}catch(FileNotFoundException exec){
			System.err.println("Fichier meilleutScore.bin introuvable créeation d'un nouveau fichier du même nom (le meilleur score a été perdu...)");
			try{
				fichierMeilleurScore.createNewFile();
			} catch(IOException exec2){
				System.err.println("Fichier meilleutScore.bin n'a pas pû être crée...");
			}
		}		
	}

	/**
	* Méthode qui test la victoire. 
	*/
	public void gagnee(){
		jeu.setVictoire(true); 
		afficher.getBoutonTricher().setVisible(false);
		afficher.getFenetreJeu().dispose();
		executerFin();
	}

	 /**
    * Cette redéfinition de la méthode actionPerformed de l'Interface <code>ActionListener</code> permet de gèrer les actions de l'utilisateur dans le menu principal notament par le bais de composants graphiques qui sont dans la Vue.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void actionPerformed(ActionEvent evenement){
		if(evenement.getSource() == fin.getBoutonQuiterFin()){
			fin.getFenetreFin().dispose();
			System.exit(0);
		}
	}

}