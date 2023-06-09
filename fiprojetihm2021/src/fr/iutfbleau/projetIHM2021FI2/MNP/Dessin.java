package fr.iutfbleau.projetIHM2021FI2.MNP;
import fr.iutfbleau.projetIHM2021FI2.API.*;

import javax.swing.JComponent;
import java.awt.Graphics;
import java.util.Arrays;
import java.awt.Color;
import java.time.LocalDate;

/**
* Une classe permetant d'afficher un graphique où les points indiquent le taux d'occupation
*
*/ 
public class Dessin extends JComponent {

  /**
  * Atribut permettant de relier le modèle qui est ReservationFactoryNP à cette classe grâce au constructeur
  *
  */
  private ReservationFactory model;

  /**
  * Atribut permettant afficher les valeurs en abscisse permettant d'indiquer pour 7 jours le taux d'occupation
  *
  */
  private int valeurX[] = {10,110,210,310,410,510,610};

  /**
  * Atribut permettant afficher les valeurs en ordonnée permettant d'indiquer pour 7 jours le taux d'occupation
  *
  */
  private int valeurY1[] = new int[7];

  /**
  * Atribut permettant afficher les valeurs en ordonnée permettant d'indiquer pour 3 jours le taux d'occupation
  *
  */
  private int valeurY2[] = new int[3];

  /**
  * Atribut permettant afficher les valeurs en abscisse permettant d'indiquer pour 3 jours le taux d'occupation
  *
  */
  private int valeurX2[] = {10,110,210};

  /**
  * Atribut permettant de récupérer la date choisie par l'utilisateur comme référence pour le graphique
  *
  */
  private String date;

  /**
  * Atribut permettant de séparer le texte reçu depuis l'attribut date pour pouvoir avoir accès à l'année, le mois et le jour
  *
  */
  private String[] parts;

  /**
  * Atribut permettant de mettre par défaut le nombre de jour choisi à 3 pour le graphique
  *
  */
  private int jours = 3;

  /**
  * Construteur pour récupérer le modèle qui est ReservationFactoryNP
  *
  */
  public Dessin(ReservationFactory model){
    this.model = model;

    
  }

  /**
  * @see paintComponent
  * @param  date une date en String
  * @param  jours nombre de jours en int
  * Méthode permetant de dessiner et d'afficher (réactualiser) le graphique avec les points grâce l'intéraction avec l'utilisateur 
  *
  */
  public void dessine(String date, int jours){
        this.date = date;
        this.parts = date.split("-");
        this.jours = jours;
        
      for(int i=0; i<jours; i++){
        if(jours == 7){
        System.out.println(i);
        this.valeurY1[i] = this.model.getRatio(LocalDate.of(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), Integer.parseInt(parts[2])+i));
        System.out.println(valeurY1[i]); 
      } else if(jours == 3){
        System.out.println(i);
        this.valeurY2[i] = this.model.getRatio(LocalDate.of(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), Integer.parseInt(parts[2])+i));
        System.out.println(valeurY2[i]);        
      }          
    }

    this.repaint();

  }

  /**
  * @param  pinceau un pinceau de type Graphics
  * Méthode qui redéfinie paintComponent permatant de dessiner et d'afficher le graphique notament dès l'instanciation de Dessin 
  *
  */
  @Override
  protected void paintComponent(Graphics pinceau) {
    // obligatoire : on crée un nouveau pinceau pour pouvoir le modifier plus tard
    Graphics secondPinceau = pinceau.create();
    // obligatoire : si le composant n'est pas censé être transparent
    if (this.isOpaque()) {
      // obligatoire : on repeint toute la surface avec la couleur de fond
      secondPinceau.setColor(this.getBackground());
      secondPinceau.fillRect(0, 0, this.getWidth(), this.getHeight());
    }
    // maintenant on dessine ce que l'on veut
    secondPinceau.setColor(this.getForeground());
    secondPinceau.drawLine(10,10,this.getWidth()-10,10);
    secondPinceau.drawLine(10,this.getHeight()-10,10,10);
    secondPinceau.drawString("0", 10, 10);
    secondPinceau.drawString(Integer.toString(Math.round(this.getHeight()/10*10)), 10, this.getHeight()-20);
    secondPinceau.drawString(Integer.toString(Math.round(this.getWidth()/10*10)), this.getWidth()-50, 10);
    for(int i=0; i<=this.getWidth(); i++){
      for(int y=0; y<=this.getHeight();y++){
         if(y%100==0){
            secondPinceau.drawString(Integer.toString(Math.round(y/10*10)), 10, y-20);
            secondPinceau.drawLine(10,y,15,y);
         }
      }
      if(i%100==0){
          if(i==Math.round(this.getWidth()/10*10)){
            secondPinceau.drawString(Integer.toString(Math.round(i/10*10)), i-50, 10);
            secondPinceau.drawLine(i,10,i,20);
          } else{
            secondPinceau.drawString(Integer.toString(Math.round(i/10*10)), i-50, 10);
            secondPinceau.drawLine(i,10,i,15);
          }
         }
    }
    secondPinceau.fill3DRect(10,10,10,10,true);
    secondPinceau.setColor(Color.RED);
    if(jours == 7){
      secondPinceau.drawPolyline(valeurX, valeurY1, 7);
    } else if(jours == 3){
      secondPinceau.drawPolyline(valeurX2, valeurY2, 3);
    }
    
    for(int i=0; i<=this.getWidth(); i++){
      for(int y=0; y<=this.getHeight();y++){
        for(int n=0; n < 7; n++){
         if(y==valeurY1[n] && i==valeurX[n]){
            secondPinceau.fill3DRect(i-5,y-5,10,10,true);
         }
       }
      }
    }
  }
}