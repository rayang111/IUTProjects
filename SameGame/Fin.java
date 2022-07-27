import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.ImageIcon;


public class Fin{
	/**
	*	Attribut qui designe la fentre du menu fin
	*/
	private JFrame fenetreFin = new JFrame("Victoire !");
	/**
	*	Attribut qui designe l'imge du menu fin
	*/
	private JLabel imghg = new JLabel();
	/**
	*	Attribut qui designe le gif de fin lorsqu'on a gangné
	*/
	private JLabel imgetat = new JLabel();
	/**
	*	Attribut qui contient la phrase de victoire
	*/
	private JLabel victoireTexte = new JLabel("Vous avez gagnee !");
	/**
	*	Attribut qui designe le bouton quitter
	*/
	private JButton quitterFin = new JButton("Quitter");
	/**
	*	Attribut qui designe le fichier qui permet de mettre l'image de fond
	*/
    private ImageIcon imagefin = new ImageIcon("./pics/hg.gif");
    /**
	*	Attribut qui designe le fichier qui permet de mettre l'image de fond
	*/
	private ImageIcon etat = new ImageIcon("./pics/gagne.gif");
	/**
	*	Attribut qui contient la phrase de meilleur score
	*/
	private JLabel meilleurScoreLabel = new JLabel("Meilleur score : ");
	/**
    * Attribut qui appel la classe FinModel. 
    */
	private FinModel finModel;
	/**
    * Attribut qui appel la classe Jeu. 
    */
	private Jeu jeu;

	/**
    *  Ce constructeur est appelé dans la classe <code>JeuObs</code> et <code>Observateur</code>.
    *  @param finModel fait appel la classe FinModel
    *  @param jeu fait appel la classe Jeu
    */
	public Fin(FinModel finModel, Jeu jeu){
		this.jeu = jeu;
		this.finModel = finModel;
	}
	/**
	* Méthode qui affiche le menu de fin. 
	*/
	public void afficherFin(){
		JLabel scoreTexte = new JLabel();
		JPanel panneauFinScore = new JPanel();
		JPanel panneauFin = new JPanel();
		GridLayout gestionaireFinScore = new GridLayout(3,1);
		GridLayout gestionaireFin = new GridLayout(2,1);
    	imgetat.repaint();
    	panneauFin.setLayout(gestionaireFin);
    	panneauFinScore.setLayout(gestionaireFinScore);
		fenetreFin.setLocation(0,0);
		fenetreFin.setIconImage(Toolkit.getDefaultToolkit().getImage("./pics/icon.png"));
		fenetreFin.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		fenetreFin.setResizable(false);
		victoireTexte.setFont(new Font("Arial", Font.BOLD, 20));
		victoireTexte.setForeground(Color.ORANGE);
		victoireTexte.setBackground(Color.DARK_GRAY);
		scoreTexte.setBackground(Color.GRAY);
		scoreTexte.setForeground(Color.WHITE);
		victoireTexte.setOpaque(true);
		scoreTexte.setOpaque(true);
		imghg.setHorizontalAlignment(JLabel.CENTER);
		scoreTexte.setHorizontalAlignment(JLabel.CENTER);
		imgetat.setHorizontalAlignment(JLabel.CENTER);
		victoireTexte.setHorizontalAlignment(JLabel.CENTER);
		scoreTexte.setText("Votre score est de " + Integer.toString(jeu.getScore()) + " points !");
		if(finModel.getScoreSuperieur()){
			meilleurScoreLabel.setText("Meilleur score : " + Integer.toString(jeu.getMeilleurScore()) + " points ! \n\nNOUVEAU RECORD !");
			meilleurScoreLabel.setForeground(Color.CYAN);
		}else{
			meilleurScoreLabel.setText("Meilleur score : " + Integer.toString(jeu.getMeilleurScore()) + " points.");
			meilleurScoreLabel.setForeground(Color.WHITE);
		}
		meilleurScoreLabel.setHorizontalAlignment(JLabel.CENTER);
		meilleurScoreLabel.setBackground(Color.BLACK);
		meilleurScoreLabel.setOpaque(true);
        imghg.setIcon(imagefin);
        imgetat.setIcon(etat);
        imgetat.setBackground(new Color(60,41,12));
        imgetat.setOpaque(true);
        quitterFin.setBackground(Color.WHITE);
        panneauFin.add(imghg);
        panneauFinScore.add(victoireTexte);
        panneauFinScore.add(scoreTexte);
        panneauFinScore.add(meilleurScoreLabel);
        panneauFin.add(panneauFinScore);
        fenetreFin.add(imgetat, BorderLayout.NORTH);
        fenetreFin.add(panneauFin, BorderLayout.CENTER);
        fenetreFin.add(quitterFin, BorderLayout.SOUTH);
        fenetreFin.pack();
        fenetreFin.setLocationRelativeTo(null);
        fenetreFin.setVisible(true);	
	}

	/**
	* Méthode (un getter) qui permet d'accèder à l'attribut qui designe le bouton quitter (qui a un accès en private). 
	*
	* @return Le bouton de fin.
	*/
	public JButton getBoutonQuiterFin(){
		return this.quitterFin;
	}
	/**
	* Méthode (un getter) qui permet d'accèder à l'attribut qui contient la phrase de victoire (qui a un accès en private). 
	*
	* @return La phrase de victoire.
	*/
	public JLabel getVictoire_texte(){
		return this.victoireTexte;
	}
	/**
	* Méthode (un getter) qui permet d'accèder à l'attribut qui designe la fentre du menu fin (qui a un accès en private). 
	*
	* @return la fentre du menu fin.
	*/
	public JFrame getFenetreFin(){
		return this.fenetreFin;
	}
	/**
	* Méthode (un setter) qui permet de modifier l'atribut qui designe le fichier qui permet de mettre l'image de fond (qui a un accès en private). 
	*
	* @param etat le fichier qui permet de mettre l'image de fond.
	*/
	public void setImageFin(ImageIcon img){
		this.imagefin = img;
	}
	/**
	* Méthode (un setter) qui permet de modifier l'atribut qui designe le fichier qui permet de mettre l'image de fond (qui a un accès en private). 
	*
	* @param etat le fichier qui permet de mettre l'image de fond.
	*/
	public void setImageEtatFin(ImageIcon img){
		this.etat = img;
	}
	/**
	* Méthode (un getter) qui permet d'accèder à l'attribut qui designe le fichier qui permet de mettre l'image de fond (qui a un accès en private). 
	*
	* @return le fichier qui permet de mettre l'image de fond.
	*/	
	public ImageIcon getImageFin(){
		return this.imagefin;
	}
	/**
	* Méthode (un getter) qui permet d'accèder à l'attribut qui designe le fichier qui permet de mettre l'image de fond (qui a un accès en private). 
	*
	* @return le fichier qui permet de mettre l'image de fond.
	*/
	public ImageIcon getImageEtatFin(){
		return this.etat;
	}
}