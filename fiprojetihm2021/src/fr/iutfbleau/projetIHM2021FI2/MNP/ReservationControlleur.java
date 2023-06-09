package fr.iutfbleau.projetIHM2021FI2.MNP;
import fr.iutfbleau.projetIHM2021FI2.API.*;

import java.awt.event.*;
import java.util.*;
import java.time.LocalDate;
import javax.swing.*;

public class ReservationControlleur implements ActionListener, FocusListener{

	/**
    * Un atribut pour récupérer la vue Reservations avec le constructeur.
    *
    */
	private Reservations vue;


	/**
    * Un atribut pour récupérer le modèle PrereservationFactory avec le constructeur.
    *
    */
	private PrereservationFactory model;


	/**
    * Un atribut pour récupérer le modèle ReservationFactory avec le constructeur.
    *
    */
	private ReservationFactory modelR;


	/**
    * Un atribut pour récupérer la classe gérant les bases de données avec le constructeur.
    *
    */
	private BaseDonnee bd;
    
    /**
    * Un atribut pour créer une boîte de dialogue notament pour la gestion des erreurs.
    *
    */
	private JOptionPane message = new JOptionPane();


	/**
	* @param vue la vue Reservations
	* @param model le modèle PrereservationFactoryNP
	* @param modelR le deuxième modèle ReservationFactoryNP
	* @param bd la base de données 
    * Constucteur du controlleur.
    *
    */
	public ReservationControlleur(Reservations vue, PrereservationFactory model, ReservationFactory modelR, BaseDonnee bd){
		this.vue = vue;
		this.model = model;
		this.modelR = modelR;
		this.bd = bd;

		this.vue.getBoutonRecherche().addActionListener(this);
		this.vue.getBoutonRechercheReference().addActionListener(this);
		this.vue.getChampRecherche().addActionListener(this);
		this.vue.getChampRechercheNom().addFocusListener(this);
		this.vue.getChampRecherchePrenom().addFocusListener(this);
		this.vue.getChampRecherche().addFocusListener(this);
		this.vue.getBoutonConfirmer().addActionListener(this);
		this.vue.getBoutonReserver().addActionListener(this);
		this.vue.getBoutonAfficherToutesReservation().addActionListener(this);
		this.vue.getBoutonRetour().addActionListener(this);
		this.vue.getBoutonQuitter().addActionListener(this);

	}

	/**
	* @param evenement un evenment de type ActionEvent
	* Une redéfinition de actionPerformed qui permet définir ce qu'il faut faire lorsque on clique sur un bouton par exemple
	*
	*/
	@Override
	public void actionPerformed(ActionEvent evenement){
		if(evenement.getSource().equals(this.vue.getBoutonRecherche())){
			try{
				this.vue.getTableModel().setRowCount(0);
				String nom = this.vue.getChampRechercheNom().getText();
				String prenom = this.vue.getChampRecherchePrenom().getText();
				this.vue.setResulatPreservations(this.model.getPrereservations(nom, prenom));
				this.vue.initialisationTableauReservation();
				this.vue.afficherClients();
			} catch(NullPointerException e){
				message.showMessageDialog(null, "Erreur : vous n'avez rien saisi", "Erreur", JOptionPane.ERROR_MESSAGE);
			}
		}
		if(evenement.getSource().equals(this.vue.getBoutonRechercheReference())){
			try{
				this.vue.getTableModel().setRowCount(0);
				String reference = this.vue.getChampRecherche().getText();
				this.vue.setResulatPreservation(this.model.getPrereservation(reference));
				this.vue.initialisationTableauReservation();
				this.vue.listerClients();
			} catch(NullPointerException e){
				message.showMessageDialog(null, "Erreur : vous n'avez rien saisi", "Erreur", JOptionPane.ERROR_MESSAGE);
			}
		}
		if(evenement.getSource().equals(this.vue.getBoutonConfirmer())){
			try{
				this.vue.getTableModelChambre().setRowCount(0);
				this.vue.setResulatChambre(this.bd.getChambreLibres((TypeChambre) this.vue.getTable().getModel().getValueAt(this.vue.getTable().getSelectedRow(),6)));
				this.vue.initialisationTableauChambre();
				this.vue.choixChambres();
			} catch(ArrayIndexOutOfBoundsException e){
				message.showMessageDialog(null, "Erreur : vous n'avez rien saisi", "Erreur", JOptionPane.ERROR_MESSAGE);
			}
		}
		if(evenement.getSource().equals(this.vue.getBoutonReserver())){
			try{
				String prenom = (String) this.vue.getTable().getModel().getValueAt(this.vue.getTable().getSelectedRow(),0);
				String nom = (String) this.vue.getTable().getModel().getValueAt(this.vue.getTable().getSelectedRow(),1);
				int nbCient = (int)this.vue.getTable().getModel().getValueAt(this.vue.getTable().getSelectedRow(),2);
				String reference = (String) this.vue.getTable().getModel().getValueAt(this.vue.getTable().getSelectedRow(),3);
				LocalDate date = (LocalDate) this.vue.getTable().getModel().getValueAt(this.vue.getTable().getSelectedRow(),4);
				int jours = (int) this.vue.getTable().getModel().getValueAt(this.vue.getTable().getSelectedRow(),5);
				TypeChambre chambre = (TypeChambre) this.vue.getTable().getModel().getValueAt(this.vue.getTable().getSelectedRow(),6);
				Client client = new ClientNP(nbCient, prenom, nom);
				Prereservation prereservation = new PrereservationNP(reference, date, jours, chambre, client);
				Chambre chambreNP = new ChambreNP((int) this.vue.getTableChambre().getModel().getValueAt(this.vue.getTableChambre().getSelectedRow(), 0), chambre);
				this.modelR.createReservation(prereservation, chambreNP);
				message.showMessageDialog(null, "Succès : Réservation ajoutée", "Succès", JOptionPane.INFORMATION_MESSAGE);
			} catch(ArrayIndexOutOfBoundsException e){
				message.showMessageDialog(null, "Erreur : vous n'avez rien saisi", "Erreur", JOptionPane.ERROR_MESSAGE);
			}
		}
		if(evenement.getSource().equals(this.vue.getBoutonAfficherToutesReservation())){
			JOptionPane dialogueDate = new JOptionPane();
			try{
			String date = dialogueDate.showInputDialog(this.vue.getFenetre(), "Entrez une date (format aaaa-mm-jj) : ", "Date requise", JOptionPane.QUESTION_MESSAGE);
			String dateParts[] = date.split("-");
			this.vue.getTableReserModel().setRowCount(0);
			this.vue.setReservation(this.modelR.getReservation(LocalDate.of(Integer.parseInt(dateParts[0]),Integer.parseInt(dateParts[1]),Integer.parseInt(dateParts[2]))));
			this.vue.initialisationTableauReser();
			this.vue.listerReservation();
			} catch(NullPointerException e){
				
			}

		}

		if(evenement.getSource().equals(this.vue.getBoutonRetour())){
			this.vue.retourTableauReservation();
		}

		if(evenement.getSource().equals(this.vue.getBoutonQuitter())){
			this.vue.getFenetre().dispose();
			System.exit(0);
		}
	}

	/**
	* @param e un evenment de type FocusEvent
	* Une redéfinition de focusGained qui permet définir ce qu'il faut faire lorsque on clique sur un texte (par exemple un champ de texte)
	*
	*/
	@Override
    public void focusGained(FocusEvent e) {
    	if(e.getSource().equals(this.vue.getChampRechercheNom())){
    		this.vue.getChampRechercheNom().setText("");
    	} else if(e.getSource().equals(this.vue.getChampRecherchePrenom())){
    		this.vue.getChampRecherchePrenom().setText("");
    	} else if(e.getSource().equals(this.vue.getChampRecherche())){
    		this.vue.getChampRecherche().setText("");
    	}
    }

	/**r
	* @param e un evenment de type FocusEvent
	* Une redéfinition de focusLost qui permet définir ce qu'il faut faire lorsque on clique sur un autre texte (par exemple un champ de texte)
	*
	*/
    @Override
    public void focusLost(FocusEvent e) {}


}