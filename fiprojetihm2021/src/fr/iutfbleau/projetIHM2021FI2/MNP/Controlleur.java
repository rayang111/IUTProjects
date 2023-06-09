package fr.iutfbleau.projetIHM2021FI2.MNP;
import fr.iutfbleau.projetIHM2021FI2.API.*;

import java.awt.event.*;

/**
* Un controlleur permettant de gérer les actions de la vue Graphique. 
*
*/ 
public class Controlleur implements ActionListener{

	private Graphique vue;
	private BaseDonnee model;
	private Statistiques stats;
	private Reservations reser;
	private PrereservationFactory modelReser;
	private ReservationFactory modelR;

	/**
	* Un constructeur pour initialiser le controlleur avec la vue et le modèle 
	*
	*/
	public Controlleur(Graphique vue, BaseDonnee model){
		this.vue = vue;
		this.model = model;

		this.vue.getBoutonGraphique().addActionListener(this);
		this.vue.getBoutonReservation().addActionListener(this);

	}

	/**
	* @param evenement un evenment de type ActionEvent
	* Une redéfinition de actionPerformed qui permet définir ce qu'il faut faire lorsque on clique sur un bouton par exemple
	*
	*/
	@Override
	public void actionPerformed(ActionEvent evenement){
		if(evenement.getSource().equals(this.vue.getBoutonGraphique())){
			modelR = new ReservationFactoryNP(this.model);
			stats = new Statistiques(this.modelR);
			StatistiquesControleur statsControlleur = new StatistiquesControleur(this.modelR, this.stats);
		}
		if(evenement.getSource().equals(this.vue.getBoutonReservation())){
			modelReser = new PrereservationFactoryNP(this.model);
			modelR = new ReservationFactoryNP(this.model);
			reser = new Reservations(this.modelReser);
			ReservationControlleur controlleurReser = new ReservationControlleur(this.reser, this.modelReser, this.modelR, this.model);
		}
	}
}