import java.awt.event.*;
import java.io.File;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import java.io.IOException;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;

public class ReglesObs implements ActionListener{

	/**
    * Attribut qui appel la classe ReglesModel. 
    */
	private ReglesModel reglesModel;
	/**
    * Attribut qui appel la classe Regles. 
    */
	private Regles regles;

	/**
    *  Ce constructeur est appelé dans la classe <code>Jeu</code>.
	*  @param regles fait appel la classe Regles
	*  @param reglesModel fait appel la classe ReglesModel
    */
	public ReglesObs(ReglesModel reglesModel, Regles regles){
		this.reglesModel = reglesModel;
		this.regles = regles;

		this.regles.getQuitterReglesButton().addActionListener(this);

		this.reglesModel.ouvertureFichier();
		this.regles.afficherRegles();
	}

	 /**
    * Cette redéfinition de la méthode actionPerformed de l'Interface <code>ActionListener</code> permet de gèrer les actions de l'utilisateur dans le menu d'options notament par le bais de composants graphiques qui sont dans la Vue.
    * @param evenement L'évenement produit par l'utilisateur. 
    */
	@Override
	public void actionPerformed(ActionEvent evenement){
		if(evenement.getSource() == regles.getQuitterReglesButton()){
			reglesModel.setTexteComplet("");
			regles.getFenetreRegles().dispose();
			if(reglesModel.getFlux() != null){
    			try {
        			reglesModel.getFlux().close();
      			} catch(IOException e) {
        			System.err.println("Impossible de fermer le fichier regles.txt !");
      			}
    		}
		}
	}

}