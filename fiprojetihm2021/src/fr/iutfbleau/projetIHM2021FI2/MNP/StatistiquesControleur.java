package fr.iutfbleau.projetIHM2021FI2.MNP;
import fr.iutfbleau.projetIHM2021FI2.API.*;

import java.awt.event.*;
import java.util.*;
import java.time.LocalDate;
import javax.swing.*;

public class StatistiquesControleur implements ActionListener{
	
	/**
    * Un atribut pour récupérer le modèle ReservationFactory avec le constructeur.
    *
    */
	private ReservationFactory model;

	/**
    * Un atribut pour récupérer la vue Statistiques avec le constructeur.
    *
    */
	private Statistiques stats;

    /**
    * Un atribut pour créer une boîte de dialogue notament pour obtenir des données.
    *
    */
	private JOptionPane dialogue = new JOptionPane();

	/**
	* Un constructeur du controlleur de l'IHM des Statistiques
	*
	* @param model le modèle ReservationFactory pour accèder à la base de données notament
	* @param stats la vue Statistisques pour y accèder depuis le controlleur (ici)
	*/
	public StatistiquesControleur(ReservationFactory model, Statistiques stats){
		this.model = model;
		this.stats = stats;

		this.stats.getBoutonValider().addActionListener(this);
		this.stats.getBoutonQuitter().addActionListener(this);
		this.stats.getBoutonValiderRatio().addActionListener(this);
	}

	/**
	* @param evenement un evenment de type ActionEvent
	* Une redéfinition de actionPerformed qui permet définir ce qu'il faut faire lorsque on clique sur un bouton par exemple
	*
	*/
	@Override
	public void actionPerformed(ActionEvent e){
		if(e.getSource().equals(this.stats.getBoutonValider())){
			String[] optionsDialogue = {"7 jours", "3 jours"};
			int choixJours = this.dialogue.showOptionDialog(this.stats.getFenetre(), "Sur combien de jours voulez vous avoir de données ?", "Choix jours",0 ,JOptionPane.QUESTION_MESSAGE, null, optionsDialogue, "");
			int jours = 0;
			if(choixJours == 0){
				jours = 7;
			} else if(choixJours == 1){
				jours = 3;
			}
			String date = this.dialogue.showInputDialog(this.stats.getFenetre(), "Saisisez une date au format aa-mm-jj", "Date requise", JOptionPane.QUESTION_MESSAGE);
			this.stats.getDessin().dessine(date, jours);
			this.stats.getFenetre().revalidate();
		}

		if(e.getSource().equals(this.stats.getBoutonValiderRatio())){
			String[] optionsDialogue = {"Sur un jour", "Sur deux jours"};
			String[] optionsDialogueType = {"Un lit simple", "Deux lits simples", "Un lit double", "Aucun"};
			int choixDate = this.dialogue.showOptionDialog(this.stats.getFenetre(), "Sur combien de jours voulez vous avoir de données ?", "Choix jours",0 ,JOptionPane.QUESTION_MESSAGE, null, optionsDialogue, "");
			int res = 0;
			if(choixDate == 0){
				String date = this.dialogue.showInputDialog(this.stats.getFenetre(), "Saisisez une date au format aa-mm-jj", "Date requise", JOptionPane.QUESTION_MESSAGE);
				String parts[] = date.split("-");
				int choixType = this.dialogue.showOptionDialog(this.stats.getFenetre(), "Sur quel type de chambre voulez vous avoir de données ?", "Choix type",0 ,JOptionPane.QUESTION_MESSAGE, null, optionsDialogueType, "");
				if(choixType == 3){
					res = this.model.getRatio(LocalDate.of(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), Integer.parseInt(parts[2])));
				} else if(choixType == 0){
					res = this.model.getRatio(LocalDate.of(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), Integer.parseInt(parts[2])), TypeChambre.UNLS);
				} else if(choixType == 1){
					res = this.model.getRatio(LocalDate.of(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), Integer.parseInt(parts[2])), TypeChambre.DEUXLS);
				} else if(choixType == 2){
					res = this.model.getRatio(LocalDate.of(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), Integer.parseInt(parts[2])), TypeChambre.UNLD);
				}
				
			} else if(choixDate == 1){
				String date = this.dialogue.showInputDialog(this.stats.getFenetre(), "Saisisez une date au format aa-mm-jj", "Date requise", JOptionPane.QUESTION_MESSAGE);
				String parts[] = date.split("-");
				String date2 = this.dialogue.showInputDialog(this.stats.getFenetre(), "Saisisez une deuxième date au format aa-mm-jj", "Date requise", JOptionPane.QUESTION_MESSAGE);
				String parts2[] = date2.split("-");
				int choixType = this.dialogue.showOptionDialog(this.stats.getFenetre(), "Sur quel type de chambre voulez vous avoir de données ?", "Choix type",0 ,JOptionPane.QUESTION_MESSAGE, null, optionsDialogueType, "");
				if(choixType == 3){
					res = this.model.getRatio(LocalDate.of(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), Integer.parseInt(parts[2])), LocalDate.of(Integer.parseInt(parts2[0]), Integer.parseInt(parts2[1]), Integer.parseInt(parts2[2])));
				} else if(choixType == 0){
					res = this.model.getRatio(LocalDate.of(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), Integer.parseInt(parts[2])), LocalDate.of(Integer.parseInt(parts2[0]), Integer.parseInt(parts2[1]), Integer.parseInt(parts2[2])), TypeChambre.UNLS);
				} else if(choixType == 1){
					res = this.model.getRatio(LocalDate.of(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), Integer.parseInt(parts[2])), LocalDate.of(Integer.parseInt(parts2[0]), Integer.parseInt(parts2[1]), Integer.parseInt(parts2[2])), TypeChambre.DEUXLS);
				} else if(choixType == 2){
					res = this.model.getRatio(LocalDate.of(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), Integer.parseInt(parts[2])), LocalDate.of(Integer.parseInt(parts2[0]), Integer.parseInt(parts2[1]), Integer.parseInt(parts2[2])), TypeChambre.UNLD);
				}
				
			}			

			this.dialogue.showMessageDialog(this.stats.getFenetre(), "Taux occupation : " + res + "%", "Résulat", JOptionPane.QUESTION_MESSAGE);
		}

		if(e.getSource().equals(this.stats.getBoutonQuitter())){
			this.stats.getFenetre().dispose();
			System.exit(0);			
		}
	}


}