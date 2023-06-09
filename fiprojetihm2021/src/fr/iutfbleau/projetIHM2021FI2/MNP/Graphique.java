package fr.iutfbleau.projetIHM2021FI2.MNP;
import fr.iutfbleau.projetIHM2021FI2.API.*;

import javax.swing.*;
import java.awt.*;
import java.util.Arrays;
 
/**
* La classe Graphique est une vue qui permet de choisir l'IHM a éxecuter.
*
*/ 
public class Graphique {

  /**
  * Un attribut pour accèder grâce au constructeur à la classe gérant les bases de données. 
  *
  */ 
  private BaseDonnee model;
  
  /**
  * Un attribut pour créer un bouton pour ouvrir l'IHM des statistiques. 
  *
  */ 
  private JButton boutonGraphique;

  /**
  * Un attribut pour créer un bouton pour ouvrir l'IHM des réservations. 
  *
  */ 
  private JButton boutonReservation;

  /**
  * Constructeur
  *
  */
  public Graphique(BaseDonnee model){
    this.model = model;
    JFrame fenetre = new JFrame();
    fenetre.setSize(200, 200);
    fenetre.setLocation(100, 100);
    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    boutonGraphique = new JButton("Graphique");
    boutonReservation = new JButton("Reservation");
    fenetre.add(boutonGraphique, BorderLayout.NORTH);
    fenetre.add(boutonReservation, BorderLayout.SOUTH);
    fenetre.setVisible(true);
  }

  /**
  * Un getter pour obtenir dans le constructeur le bouton pour lançer l'IHM des statistiques.
  *
  */ 
  public JButton getBoutonGraphique(){
    return boutonGraphique;
  }
  /**
  * Un getter pour obtenir dans le constructeur le bouton pour lançer l'IHM des Réservations Booking.
  *
  */ 
  public JButton getBoutonReservation(){
    return boutonReservation;
  }

}