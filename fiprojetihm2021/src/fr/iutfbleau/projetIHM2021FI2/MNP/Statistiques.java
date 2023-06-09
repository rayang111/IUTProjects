package fr.iutfbleau.projetIHM2021FI2.MNP;
import fr.iutfbleau.projetIHM2021FI2.API.*;

import javax.swing.*;
import java.awt.*;
import javax.swing.border.*;

public class Statistiques{

	/**
    * Un gestionnaire pour les boutons.
    *
    */
	private GridLayout gestionnaire = new GridLayout(1,3);

	/**
    * Un bouton pour pouvoir faire un graphique.
    *
    */
	private JButton boutonValider = new JButton("Graphique");

	/**
    * Un bouton pour pouvoir afficher un ratio.
    *
    */
	private JButton boutonValiderRation = new JButton("Voir le ratio");

	/**
    * Un bouton pour pouvoir quitter.
    *
    */
	private JButton boutonQuitter = new JButton("Quitter");

	/**
    * Un texte pour indiquer que c'est l'IHM des Statistiques.
    *
    */
	private JLabel texteChoix = new JLabel("Statistiques");
	
	/**
    * Un panneau pour regrouper les boutons entre eux.
    *
    */
	private JPanel panneauBas = new JPanel();

	/**
    * Un atribut pour créer le graphique.
    *
    */
	private Dessin graphique;

	/**
    * Un atribut pour créer la fenêtre.
    *
    */
	private JFrame fenetre = new JFrame();

	/**
    * Un constructeur pour réaliser l'interface graphique
    *
    */
	public Statistiques(ReservationFactory model){
		graphique = new Dessin(model);
		fenetre.setSize(1000, 1000);
    	fenetre.setLocation(100, 100);
    	fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	panneauBas.add(this.boutonQuitter);
    	panneauBas.add(this.boutonValider);
    	panneauBas.add(this.boutonValiderRation);
    	texteChoix.setHorizontalAlignment(JLabel.CENTER);
    	texteChoix.setBackground(Color.BLUE);
    	texteChoix.setForeground(Color.WHITE);
    	texteChoix.setOpaque(true);
    	boutonQuitter.setBackground(Color.RED);
    	boutonQuitter.setForeground(Color.WHITE);
    	boutonValider.setBackground(Color.WHITE);
    	boutonValiderRation.setBackground(Color.WHITE);
    	panneauBas.setLayout(gestionnaire);
    	texteChoix.setBorder(new EmptyBorder(10, 10, 10, 10));
    	graphique.setBorder(new EmptyBorder(10, 10, 10, 10));
    	panneauBas.setBorder(new EmptyBorder(10, 10, 10, 10));
    	fenetre.add(texteChoix, BorderLayout.NORTH);
    	fenetre.add(graphique, BorderLayout.CENTER);
    	fenetre.add(panneauBas, BorderLayout.SOUTH);
    	fenetre.setVisible(true);
	}

	/**
    * Un getter pour obtenir la fenetre.
    *
    */
	public JFrame getFenetre(){
		return this.fenetre;
	}

	/**
    * Un getter pour obtenir le bouton pour créer le graphique.
    *
    */
	public JButton getBoutonValider(){
		return this.boutonValider;
	}

	/**
    * Un getter pour obtenir le graphique.
    *
    */
	public Dessin getDessin(){
		return this.graphique;
	}

	/**
    * Un getter pour obtenir le bouton pour quitter.
    *
    */	
	public JButton getBoutonQuitter(){
		return this.boutonQuitter;
	}

	/**
    * Un getter pour obtenir le bouton pour obtenir un ratio.
    *
    */
	public JButton getBoutonValiderRatio(){
		return this.boutonValiderRation;
	}   
}