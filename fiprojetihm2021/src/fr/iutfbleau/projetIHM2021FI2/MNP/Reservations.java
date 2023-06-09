package fr.iutfbleau.projetIHM2021FI2.MNP;
import fr.iutfbleau.projetIHM2021FI2.API.*;

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.table.*;
import java.awt.*;
import java.util.*;
import java.util.Arrays;

public class Reservations{

	/**
    * Un attribut pour récupérer le modèle.
    *
    */
	private PrereservationFactory model;

	/**
    * Un attribut pour afficher un texte de bienvenue.
    *
    */
	private JLabel texteFenetre = new JLabel("Bienvenue sur le logiciel de gestion de réservations de Booking.");

	/**
    * Un attribut pour avoir un gestionnaire d'affichage.
    *
    */
	private GridLayout gestionnaireNord = new GridLayout(2,1);

	/**
    * Un attribut pour avoir un panneau pour la partie nord de l'IHM.
    *
    */	
	private JPanel panneauNord = new JPanel(gestionnaireNord);

	/**
    * Un attribut pour le contenu du tableau.
    *
    */	
	private Object[] tableau = new Object[7];


	/**
    * Un attribut pour les atributs du tableau.
    *
    */	
	private String[] nomTableau = {"prenom", "nom", "id", "reference", "debut", "jours", "categorie"};

	/**
    * Un attribut pour les attributs du tableau des réservations.
    *
    */	
	private String[] nomTableauReser = {"prenom", "nom", "id", "reference", "debut", "jours", "chambre"};

	/**
    * Un attribut pour le modèle du tableau des réservations.
    *
    */	
	private DefaultTableModel tableModel = new DefaultTableModel(nomTableau, 0);

	/**
    * Un attribut pour créer la fenêtre.
    *
    */
	private JFrame fenetre = new JFrame();

	/**
    * Un attribut pour créer un panneau pour le tableau.
    *
    */
	private JPanel panneauTableau = new JPanel();

	/**
    * Un attribut pour créer le bouton de recherche avec le nom et le prenom.
    *
    */
	private JButton boutonRecherche = new JButton("Recherche avec nom et prénom");

	/**
    * Un attribut pour créer le bouton de recherche avec la référence.
    *
    */
	private JButton boutonRechercheReference = new JButton("Recherche avec référence");

	/**
    * Un attribut pour créer le bouton confirmer.
    *
    */
	private JButton boutonConfirmer = new JButton("Confirmer");

	/**
    * Un attribut pour créer un panneau pour le tableau de la recherche des réservations.
    *
    */
	private JPanel panneauRecherche = new JPanel();

	/**
    * Un attribut pour le champ de texte pour entrer la référence.
    *
    */
	private JTextField champRecherche = new JTextField("Entrez une référence");

	/**
    * Un attribut pour afficher le texte "ou".
    *
    */
	private JLabel texteOu = new JLabel("ou");

	/**
    * Un attribut pour créer un champ de texte pour entrer le nom.
    *
    */
	private JTextField champRechercheNom = new JTextField("Nom");

	/**
    * Un attribut pour créer un champ de texte pour entrer le prénom.
    *
    */
	private JTextField champRecherchePrenom = new JTextField("Prénom");

	/**
    * Un attribut pour créer le panneau pour le tableau.
    *
    */
	private JPanel panneau = new JPanel();

	/**
    * Un attribut pour créer le panneau pour le tableau des chambres.
    *
    */
	private JPanel panneauC = new JPanel();

	/**
    * Un attribut pour avoir une préréservation.
    *
    */
	private Prereservation resulatPreservation;

	/**
    * Un attribut pour avoir l'ensemble des résultat des préréservations.
    *
    */
	private Set<Prereservation> resulatPreservations;

	/**
    * Un attribut pour créer le tableau.
    *
    */
	private JTable table = new JTable(tableModel);

	/**
    * Un attribut pour créer le contenu du tableau.
    *
    */
	private Object[] tableauChambre = new Object[2];

	/**
    * Un attribut pour les atributs du tableau des chambres.
    *
    */
	private String[] nomChambre = {"numéro", "Type chambre"};

	/**
    * Un attribut pour le modèle du tableau des chambres.
    *
    */
	private DefaultTableModel tableModelChambre = new DefaultTableModel(nomChambre, 0);

	/**
    * Un attribut pour créer le tableau des chambres.
    *
    */
	private JTable tableChambre = new JTable(tableModelChambre);

	/**
    * Un attribut pour créer un panneau pour le tableau des chambres.
    *
    */
	private JPanel panneauChambre = new JPanel();

	/**
    * Un attribut pour créer un panneau pour le tableau.
    *
    */
	private JPanel panneauTableaux = new JPanel();

	/**
    * Un attribut pour créer le panneau des boutons du bas.
    *
    */
	private JPanel panneauBoutons = new JPanel();

	/**
    * Un attribut pour créer l'ensemble des résultat de la requette pour avoir l'ensemble des chambres.
    *
    */
	private Set<Chambre> resulatChambre;

	/**
    * Un attribut pour créer le bouton réserver.
    *
    */
	private JButton boutonReserver = new JButton("Réserver");

	/**
    * Un attribut pour créer le bouton pour afficher toutes les réservations.
    *
    */
	private JButton boutonAfficherToutesReservation = new JButton("Afficher toutes les reservations");

	/**
    * Un attribut pour créer le bouton retour.
    *
    */
	private JButton boutonRetour = new JButton("Retour");

	/**
    * Un attribut pour créer l'ensemble des réservations.
    *
    */
	private Set<Reservation> reservation;

	/**
    * Un attribut pour le gestionaire pour le panneau des recherches.
    *
    */
	private GridLayout gestionnaire = new GridLayout(1,6);

	/**
    * Un attribut pour le gestionaire pour le panneau des boutons.
    *
    */
	private GridLayout gestionnaireBoutons = new GridLayout(1,5);

	/**
    * Un attribut pour créer une barre de défilement.
    *
    */
	private JScrollPane tableScroll = new JScrollPane(table);

	/**
    * Un attribut pour créer une barre de défilement pour le tableau des chambres.
    *
    */
	private JScrollPane tableChambreScroll = new JScrollPane(tableChambre);

	/**
    * Un attribut pour le contenu du tableau des chambres.
    *
    */
	private Object[] tableauReser = new Object[7];

	/**
    * Un attribut pour le modèle du tableau de toutes les réservations.
    *
    */
	private DefaultTableModel tableModelReser = new DefaultTableModel(nomTableauReser, 0);

	/**
    * Un attribut pour créer le tableau de toutes les réservations.
    *
    */
	private JTable tableReser = new JTable(tableModel);

	/**
    * Un attribut pour créer la barre de défilement pour le tableau de toutes les réservations.
    *
    */
	private JScrollPane tableReserScroll = new JScrollPane(tableReser);

	/**
    * Un attribut pour le panneau du tableau de toutes les réservations.
    *
    */
	private JPanel panneauR = new JPanel();

	/**
    * Un attribut pour créer un bouton pour quitter le logiciel.
    *
    */
	private JButton boutonQuitter = new JButton("Quitter");

	/**
	* Un constructeur pour la vue Reservations
	* @param model de type PrereservationFactory
	*
	*/
	public Reservations(PrereservationFactory model){
	    this.model = model;
	    this.fenetre.setSize(1550, 500);
    	this.fenetre.setLocation(100, 100);
	    this.fenetre.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
	    this.champRecherche.setSize(100,50);
	    this.champRechercheNom.setSize(100,50);
	    this.champRecherchePrenom.setSize(100,50);
	    this.panneauRecherche.setLayout(gestionnaire);
	    this.panneauRecherche.add(champRecherche);
	    this.texteOu.setHorizontalAlignment(JLabel.CENTER);
	    this.panneauRecherche.add(texteOu);
	    this.panneauRecherche.add(champRechercheNom);
	    this.panneauRecherche.add(champRecherchePrenom);
	    this.panneauRecherche.add(boutonRecherche);
	    this.panneauRecherche.add(boutonRechercheReference);
	    this.panneauRecherche.setBorder(new EmptyBorder(10, 10, 10, 10));
	    this.panneauNord.add(texteFenetre);
	    this.texteFenetre.setHorizontalAlignment(JLabel.CENTER);
	    this.texteFenetre.setOpaque(true);
	    this.texteFenetre.setBackground(Color.BLUE);
	    this.texteFenetre.setForeground(Color.WHITE);
	    this.panneauNord.add(panneauRecherche);
	    this.fenetre.add(panneauNord, BorderLayout.NORTH);
	    this.panneau.add(table.getTableHeader(), BorderLayout.NORTH);
    	this.panneau.add(table, BorderLayout.CENTER);
    	this.panneauC.add(tableChambre.getTableHeader(), BorderLayout.NORTH);
    	this.panneauC.add(tableChambre, BorderLayout.CENTER);
    	this.panneauR.add(tableReser.getTableHeader(), BorderLayout.NORTH);
    	this.panneauR.add(tableReser, BorderLayout.CENTER);
    	this.panneauBoutons.setLayout(gestionnaireBoutons);
    	this.panneauBoutons.add(this.boutonQuitter);
    	this.panneauBoutons.add(this.boutonRetour);
		this.panneauBoutons.add(this.boutonReserver);
		this.panneauBoutons.add(this.boutonAfficherToutesReservation);
	    this.panneauBoutons.add(boutonConfirmer);
    	this.panneauTableaux.add(this.tableScroll, BorderLayout.EAST);
    	this.panneauTableaux.add(this.tableReserScroll, BorderLayout.CENTER);
    	this.panneauTableaux.add(this.tableChambreScroll, BorderLayout.WEST);
    	this.fenetre.add(this.panneauTableaux, BorderLayout.CENTER);
    	this.panneauBoutons.setBorder(new EmptyBorder(10, 10, 10, 10));
    	this.fenetre.add(this.panneauBoutons, BorderLayout.SOUTH);

    	this.table.setRowHeight(50);
    	this.tableChambre.setRowHeight(50);
    	this.tableReser.setRowHeight(50);
    	this.table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
    	this.tableReser.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
    	this.tableChambre.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
    	this.table.setDragEnabled(false);
    	this.tableChambre.setDragEnabled(false);
    	this.tableReser.setDragEnabled(false);

    	this.boutonRetour.setVisible(false);
    	this.boutonReserver.setVisible(false);
    	this.boutonQuitter.setBackground(Color.RED);
    	this.boutonQuitter.setForeground(Color.WHITE);
    	this.boutonRetour.setBackground(Color.GRAY);
    	this.boutonRetour.setForeground(Color.WHITE);
    	this.boutonReserver.setBackground(Color.GREEN);
    	this.boutonReserver.setForeground(Color.WHITE);
    	this.boutonConfirmer.setBackground(Color.BLUE);
    	this.boutonConfirmer.setForeground(Color.WHITE);
    	this.boutonAfficherToutesReservation.setBackground(Color.WHITE);
    	this.boutonRecherche.setBackground(Color.WHITE);
    	this.boutonRechercheReference.setBackground(Color.WHITE);
	    this.fenetre.setVisible(true);

	}


	public void initialisationTableauReservation(){
		this.tableChambreScroll.setVisible(false);
		this.tableReserScroll.setVisible(false);
		this.tableScroll.setVisible(true);
		this.boutonConfirmer.setVisible(true);
		this.boutonRetour.setVisible(false);
		for(int i=0; i<tableau.length; i++){
	    	this.tableau[0] = null;
	    	this.tableau[1] = null;
	    	this.tableau[2] = null;
	    	this.tableau[3] = null;   	
	    	this.tableau[4] = null;
	    	this.tableau[5] = null;
	    	this.tableau[6] = null;
	    }
	    tableScroll.setViewportView(table);
		
	    this.fenetre.revalidate();
	}

	public void retourTableauReservation(){
		this.boutonAfficherToutesReservation.setText("Afficher toutes les reservations");
		this.tableChambreScroll.setVisible(false);
		this.tableReserScroll.setVisible(false);
		this.tableScroll.setVisible(true);
		this.boutonRetour.setVisible(false);
		this.boutonReserver.setVisible(false);
		this.boutonConfirmer.setVisible(true);
		this.boutonAfficherToutesReservation.setVisible(true);
		this.fenetre.revalidate();		
	}

	public void initialisationTableauChambre(){
		this.tableChambreScroll.setVisible(true);
		this.tableScroll.setVisible(false);
		this.boutonConfirmer.setVisible(false);
		this.boutonRetour.setVisible(true);
		this.boutonReserver.setVisible(true);
		this.boutonAfficherToutesReservation.setVisible(false);
		for(int i=0; i<tableauChambre.length; i++){
	    	this.tableauChambre[0] = null;
	    	this.tableauChambre[1] = null;
	    }
		tableChambreScroll.setViewportView(tableChambre);
	    this.fenetre.revalidate();
	}

	public void initialisationTableauReser(){
		this.boutonAfficherToutesReservation.setText("Modifier la date");
		this.tableReserScroll.setVisible(true);
		this.tableScroll.setVisible(false);
		this.boutonRetour.setVisible(true);
		this.boutonConfirmer.setVisible(false);
		for(int i=0; i<tableauReser.length; i++){
	    	this.tableauReser[0] = null;
	    	this.tableauReser[1] = null;
	    	this.tableauReser[2] = null;
	    	this.tableauReser[3] = null;   	
	    	this.tableauReser[4] = null;
	    	this.tableauReser[5] = null;
	    	this.tableauReser[6] = null;
	    }
	    tableReserScroll.setViewportView(tableReser);
	    this.fenetre.revalidate();			
	}

	public void listerClients(){
			this.tableau[0] = this.resulatPreservation.getClient().getPrenom();
			this.tableau[1] = this.resulatPreservation.getClient().getNom();
	    	this.tableau[2] = this.resulatPreservation.getClient().getId();
	    	this.tableau[3] = this.resulatPreservation.getReference();
	    	this.tableau[4] = this.resulatPreservation.getDateDebut();
	    	this.tableau[5] = this.resulatPreservation.getJours();
	    	this.tableau[6] = this.resulatPreservation.getTypeChambre();
	    	this.tableModel.addRow(tableau);   
	    table.setModel(tableModel);
    	this.fenetre.repaint();
    	
	}

	public void afficherClients(){
		Iterator<Prereservation> it=this.resulatPreservations.iterator();
		Prereservation res;
		while(it.hasNext()){
			res = it.next();
				this.tableau[0] = res.getClient().getPrenom();
				this.tableau[1] = res.getClient().getNom();
		    	this.tableau[2] = res.getClient().getId();
		    	this.tableau[3] = res.getReference();
		    	this.tableau[4] = res.getDateDebut();
		    	this.tableau[5] = res.getJours();
		    	this.tableau[6] = res.getTypeChambre();
		    	this.tableModel.addRow(tableau);
		    	
		}	    
	    table.setModel(table.getModel());
    	this.fenetre.repaint();
	}

	public void choixChambres(){
		Iterator<Chambre> it=this.resulatChambre.iterator();
		Chambre res;
		while(it.hasNext()){
			res = it.next();
			this.tableauChambre[0] = res.getNumero();
			this.tableauChambre[1] = res.getType();
	    	this.tableModelChambre.addRow(tableauChambre);
	    }  
	    tableChambre.setModel(tableModelChambre);
    	this.fenetre.repaint();		
	}

	public void listerReservation(){
		Iterator<Reservation> it=this.reservation.iterator();
		Reservation res;
		while(it.hasNext()){
			res = it.next();
			this.tableauReser[0] = res.getClient().getPrenom();
			this.tableauReser[1] = res.getClient().getNom();
			this.tableauReser[2] = res.getClient().getId();
			this.tableauReser[3] = res.getReference();
			this.tableauReser[4] = res.getDateDebut();
			this.tableauReser[5] = res.getJours();
			this.tableauReser[6] = res.getChambre().getNumero();
	    	this.tableModelReser.addRow(tableauReser);
	    }
	    tableReser.setModel(tableModelReser);  
	    this.fenetre.repaint();
	}


	/**
    * Un getter pour obtenir la fenetre.
    *
    */
	public JFrame getFenetre(){
		return this.fenetre;
	}

	/**
    * Un getter pour obtenir le bouton pour effectuer une recherche.
    *
    */
	public JButton getBoutonRecherche(){
		return this.boutonRecherche;
	}

	/**
    * Un getter pour obtenir le champ où est indiqué la référence.
    *
    */
	public JTextField getChampRecherche(){
		return this.champRecherche;
	}

	/**
    * Un getter pour obtenir le champ de texte où est indiqué le nom.
    *
    */
	public JTextField getChampRechercheNom(){
		return this.champRechercheNom;
	}

	/**
    * Un getter pour obtenir le champ de texte où est indiqué le prénom.
    *
    */
	public JTextField getChampRecherchePrenom(){
		return this.champRecherchePrenom;
	}

	/**
    * Un getter pour obtenir le bouton faire une recherche avec une référence.
    *
    */
	public JButton getBoutonRechercheReference(){
		return this.boutonRechercheReference;
	}

	/**
    * Un getter pour obtenir une préréservation.
    *
    */
	public Prereservation getResulatPreservation(){
		return this.resulatPreservation;
	}

	/**
    * Un setter pour modfier une préréservation.
    *
    */
	public void setResulatPreservation(Prereservation p){
		 this.resulatPreservation = p;
	}

	/**
    * Un getter pour obtenir l'ensemble des préréservations.
    *
    */
	public Set<Prereservation> getResulatPreservations(){
		return this.resulatPreservations;
	}

	/**
    * Un getter pour obtenir l'ensemble des préréservations.
    *
    */
	public void setResulatPreservations(Set<Prereservation> p){
		 this.resulatPreservations = p;
	}

	/**
    * Un getter pour obtenir le modèle du tableau.
    *
    */
	public DefaultTableModel getTableModel(){
		return this.tableModel;
	}

	/**
    * Un getter pour obtenir le bouton confirmer.
    *
    */
	public JButton getBoutonConfirmer(){
		return this.boutonConfirmer;
	}

	/**
    * Un getter pour obtenir le tableau.
    *
    */
	public JTable getTable(){
		return this.table;
	}

	/**
    * Un getter pour obtenir le bouton pour réserver.
    *
    */
	public JButton getBoutonReserver(){
		return this.boutonReserver;
	}

	/**
    * Un setter pour modfier l'ensemble de chambres.
    *
    */
	public void setResulatChambre(Set<Chambre> c){
		this.resulatChambre = c;
	}

	/**
    * Un getter pour obtenir le tableau des chambres.
    *
    */
	public JTable getTableChambre(){
		return this.tableChambre;
	}

	/**
    * Un getter pour obtenir le modèle du tableau des chambres.
    *
    */
	public DefaultTableModel getTableModelChambre(){
		return this.tableModelChambre;
	}

	/**
    * Un getter pour obtenir le bouton pour afficher toutes les réservations.
    *
    */
	public JButton getBoutonAfficherToutesReservation(){
		return this.boutonAfficherToutesReservation;
	}

	/**
    * Un getter pour obtenir un ensemble de réservations.
    *
    */
	public Set<Reservation> getReservation(){
		return this.reservation;
	}

	/**
    * Un setter pour modifier l'ensemble des réservations.
    *
    */
	public void setReservation(Set<Reservation> r){
		this.reservation = r;
	}

	/**
    * Un getter pour obtenir le bouton retour.
    *
    */
	public JButton getBoutonRetour(){
		return this.boutonRetour;
	}

	/**
    * Un getter pour obtenir le modèle du tableau des réservations.
    *
    */
	public DefaultTableModel getTableReserModel(){
		return this.tableModelReser;
	}

	/**
    * Un getter pour obtenir le bouton pour quitter.
    *
    */
	public JButton getBoutonQuitter(){
		return this.boutonQuitter;
	}
}