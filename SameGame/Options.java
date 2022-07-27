/**
 * La classe <code>Options</code> est utilisÃ©e gerer les parrametres du jeu et notament sur le type de niveau souhaitee. Ici c'est la Vue du menu d'options, donc c'est tout ce qui sera affichÃ© à l'Ã©cran de l'utilisateur.
 *  
 * @version 1.1
 * @author Rayan GRIB
 * @author Pierre BARBEY
 */

//Importation de tout les packages pour faire fonctionner la Vue.

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.border.Border;

public class Options{

	/**
	*  Atribut qui contient la fenêtre du menu d'options.
	*/
	private JFrame fenetreOptions = new JFrame("SameGame : Options");

	/**
	*  Atribut qui contient le bouton "Fermer".
	*/
	private JButton optionsFermer = new JButton("Fermer");

	/**
	*  Atribut qui contient le bouton radio qui permet de sélectionner le fait l'utilisateur veut jouer un niveau depuis un fichier de son ordinateur.
	*/
	private JRadioButton choixFichier = new JRadioButton("Jouer un niveau depuis un fichier", false);

	/**
	*  Atribut qui contient le bouton radio qui permet de sélectionner le fait l'utilisateur veut jouer un niveau généré aléatoirement.
	*/
	private JRadioButton choixAlea = new JRadioButton("Jouer un niveau g\u00e9n\u00e9r\u00e9 al\u00e9atoirement", true);

	/**
	*  Atribut qui contient le bouton pour choisir un fichier depuis une boîte de dialogue JFileChosser (voir <code>OptionsModel</code>).
	*/
	private JButton choisir = new JButton("Choisir un fichier");

	/**
	*  Atribut qui contient la case à cocher pour activer le "mode triche" (un "mode" où on peut gagner le jeu à tout moment avec un très haut score).
	*/	
	private JCheckBox autoriserTriche = new JCheckBox("Mode triche");

	/**
	*  Atribut qui contient le panneau du bas de la fenetre du menu d'options, c'est dans ce panneau que se situe le bouton "Fermer".
	*/
	private	JPanel panneauOptionsFermer = new JPanel();

	/**
	*  Atribut qui contient le panneau centrale de la fenetre du menu d'options.
	*/
	private	JPanel panneauOptions = new JPanel();

	/**
	*  Atribut qui contient le panneau qui concentre dans la fenetre du menu d'options, les choix sur le type de niveau que l'utilisateur veut.
	*/
	private	JPanel panneauOptionsFichier = new JPanel();

	/**
	*  Atribut qui contient le groupe de boutons radio (boutons qui seront liés) pour le choix sur le type de niveau que l'utilisateur veut.
	*/
	private	ButtonGroup groupeChoix = new ButtonGroup();

	/**
	*  Atribut qui contient la description du choix que l'utilisateur doit faire sur le choix du type de niveau pour le jeu.
	*/
	private	JLabel descriptionOptionChoix = new JLabel(" Choix sur les niveaux du jeu : ");

	/**
	*  Atribut qui contient la description du choix que l'utilisateur doit faire sur le choix du thème du jeu.
	*/
	private	JLabel descriptionOptionTheme = new JLabel(" Choix sur le thème du jeu : ");

	/**
	*  Atribut qui contient la description du choix que l'utilisateur doit faire sur le mode triche.
	*/
	private	JLabel descriptionOptionTriche = new JLabel(" Choix sur le mode triche (non recommendé) : ");

	/**
	*  Atribut qui contient le panneau qui contient tout les composants sur le choix du thème du jeu.
	*/
	private	JPanel panneauOptionsTheme = new JPanel();

	/**
	*  Atribut qui contient le FlowLayout sur le panneau du choix du type de niveau pour le jeu.
	*/
	private	FlowLayout gestionnaireOptionsChoix = new FlowLayout(FlowLayout.CENTER);

	/**
	*  Atribut qui contient le GridLayout du menu d'options (s'applique sur tout sauf le panneau du choix du type de niveau).
	*/
	private	GridLayout gestionnaireOptions = new GridLayout(8,1);

	/**
	*  Atribut qui contient le panneau qui contient les composants sur le choix du mode triche.
	*/	
	private	JPanel panneauOptionsTriche = new JPanel();

	/**
	*  Atribut qui contient la bordure noire qui s'applique sur le panneau du bas de la fenetre du menu d'options.
	*/
	private	Border ligneBordure = BorderFactory.createLineBorder(Color.GRAY);

	/**
	* Atribut qui contient le Modèle du menu d'options pour y avoir accès depuis la vue (L'atribut est initialisé dans constructeur).
	*/
	private OptionsModel optionsMenuOptionsModel;

	/**
	*  Atribut qui contient le menu déroulant pour choisir le thème du jeu.
	*/	
	private JComboBox<String> choixTheme;

	/**
	* Ce constructeur permet de récupérer le Modèle du menu d'options, d'y avoir accès depuis la Vue (ici). Ce constructeur est appelé dans la classe <code>MenuPrincipalObs</code>.
	* 
	*/
	public Options(OptionsModel optionsMenuOptionsModel){
		this.optionsMenuOptionsModel = optionsMenuOptionsModel; 

	}

	/**
	* Méthode (un getter) qui permet d'accèder à la fenetre du menu d'options (qui a un accès en private). 
	*
	* @return La fenetre du menu d'options.
	*/
	public JFrame getFenetreOptions(){
		return this.fenetreOptions;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au bouton "Choisir" du menu d'options (qui a un accès en private). 
	*
	* @return Le bouton "Choisir" du menu d'options.
	*/
	public JButton getChoisir(){
		return this.choisir;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au bouton "Fermer" du menu d'options (qui a un accès en private). 
	*
	* @return Le bouton "Fermer" du menu d'options.
	*/
	public JButton getOptionsFermer(){
		return this.optionsFermer;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au bouton radio, qui symbolise la sélection d'un niveau généré avec un fichier, du menu d'options (qui a un accès en private). 
	*
	* @return Le bouton radio, qui permet de choisir de sélectionner un fichier, du menu d'options.
	*/
	public JRadioButton getChoixFichier(){
		return this.choixFichier;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au bouton radio, qui symbolise la sélection d'un niveau généré aléatoirement, du menu d'options (qui a un accès en private). 
	*
	* @return Le bouton radio, qui permet de choisir de générer un niveau aléatoirement, du menu d'options.
	*/
	public JRadioButton getChoixAlea(){
		return this.choixAlea;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au menu déroulant, qui permet de choisir un thème, du menu d'options (qui a un accès en private). 
	*
	* @return Le bouton radio, menu déroulant, qui permet de choisir un thème, du menu d'options.
	*/
	public JComboBox getChoixTheme(){
		return this.choixTheme;
	}

	/**
	* Méthode (un getter) qui permet d'accèder à la case à cocher, qui permet de choisir d'activer ou non le mode triche, du menu d'options (qui a un accès en private). 
	*
	* @return La case à cocher, qui permet de choisir d'activer ou non le mode triche, du menu d'options.
	*/	
	public JCheckBox getAutoriserTriche(){
		return this.autoriserTriche;
	}

	/**
	* Méthode (un getter) qui permet d'accèder au Modèle du menu d'options (qui a un accès en private). 
	*
	* @return Le Modèle du menu d'options.
	*/		
	public OptionsModel getMenuOptionsModel(){
		return this.optionsMenuOptionsModel;
	}

	/**
	* La méthode permet d'afficher sur l'écran de du joueur, le menu d'options avec les interactions rendues possibles (ActionListener) avec la classe <code>OptionsObs</code>.
	*/	
	public void afficherOptions(){
		choixTheme = new JComboBox<String>(optionsMenuOptionsModel.getChoixBox());
		this.fenetreOptions.setIconImage(Toolkit.getDefaultToolkit().getImage("./pics/icon.png"));
		this.fenetreOptions.setResizable(false);
		this.fenetreOptions.setLocation(40,40);
		this.fenetreOptions.setLayout(gestionnaireOptions);
		panneauOptionsFermer.add(optionsFermer);
		this.optionsFermer.setBackground(Color.WHITE);
		this.fenetreOptions.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		groupeChoix.add(choixFichier);
		groupeChoix.add(choixAlea);
		panneauOptions.setLayout(gestionnaireOptionsChoix);
		panneauOptions.add(choixFichier);
		panneauOptions.add(choixAlea);
		panneauOptionsFichier.add(choisir);
		this.choisir.setBackground(Color.WHITE);
		this.choixTheme.setBackground(Color.WHITE);
		panneauOptionsFermer.setBorder(ligneBordure);
		panneauOptionsTheme.add(choixTheme);
		panneauOptionsTriche.add(autoriserTriche);
		descriptionOptionChoix.setFont(new Font("Arial", Font.BOLD | Font.ITALIC, 12));
		descriptionOptionTheme.setFont(new Font("Arial", Font.BOLD | Font.ITALIC, 12));
		descriptionOptionTriche.setFont(new Font("Arial", Font.BOLD | Font.ITALIC, 12));
		this.fenetreOptions.add(descriptionOptionChoix);
		this.fenetreOptions.add(panneauOptions);
		this.fenetreOptions.add(panneauOptionsFichier);
		this.fenetreOptions.add(descriptionOptionTheme);
		this.fenetreOptions.add(panneauOptionsTheme);
		this.fenetreOptions.add(descriptionOptionTriche);
		this.fenetreOptions.add(panneauOptionsTriche);
		this.fenetreOptions.add(panneauOptionsFermer);
		this.fenetreOptions.pack();
		this.fenetreOptions.setLocationRelativeTo(null);
		this.fenetreOptions.setVisible(true);
	}

	/**
	* Méthode qui permet d'ouvrir une boîte de dialogue pour sélectionner un fichier.
	*/
	public void choixFichier(){
		optionsMenuOptionsModel.getPath().showOpenDialog(null);
	}


}