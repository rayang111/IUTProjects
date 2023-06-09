package fr.iutfbleau.projetIHM2021FI2.Test;
import fr.iutfbleau.projetIHM2021FI2.API.*;
import fr.iutfbleau.projetIHM2021FI2.MNP.*;
import java.time.LocalDate;
import java.util.*;
//import java.util.Random;

public class TestTexteMNP{


    public static void main(String[] args) {
        // morceaux de modèle
        BaseDonnee bd = new BaseDonnee();
        PrereservationFactoryNP bookingPointCom = new PrereservationFactoryNP(bd);

        Client c1 =  new ClientNP(1,"Marine","Carpentier");
        Client c2 =  new ClientNP(2, "Aaron","Dumas");
        Client c3 =  new ClientNP(3, "Kimberley", "Leroux");	
        Client c4 =  new ClientNP(4, "Florentin", "Giraud");	
        Client c5 =  new ClientNP(5, "Martin", "Gillet");	

        bookingPointCom.ajoutePrereservation("4751-3708-LRFM", LocalDate.of(2018,01,5),1, TypeChambre.DEUXLS,c1);
        bookingPointCom.ajoutePrereservation("2436-3909-NXLL", LocalDate.of(2018,01,07),1, TypeChambre.UNLS,c1);
        bookingPointCom.ajoutePrereservation("1351-0775-BETZ", LocalDate.of(2018,01,05),2, TypeChambre.DEUXLS,c2);
        bookingPointCom.ajoutePrereservation("3440-0631-NFCU", LocalDate.of(2018,01,06),2, TypeChambre.UNLD,c2);
        bookingPointCom.ajoutePrereservation("1499-2254-DBIU", LocalDate.of(2018,01,04),2, TypeChambre.UNLS,c2);
        bookingPointCom.ajoutePrereservation("5660-8953-YKJO", LocalDate.of(2018,01,06),2, TypeChambre.DEUXLS,c5);

        // une fois que le modèle de PrereservationFactoryNP a du contenu, je peux le caster en l'interface PreservationFactory de l'API correspondante pour que la vue s'en serve.
        
        PrereservationFactory bookingPointComAPISeulement = bookingPointCom;
        System.out.print("Le modèle de Préréservation est prêt.\n");

        
        // Idem ici avec un modèle non persistant de Réservation.
        ReservationFactory grandLivreDOrAPISeulement  = new ReservationFactoryNP(bd);

        

        // Normalement ce qu'il faut pour faire marcher la vue sont créées ci-dessous.
        // Il faut probablement leur donner accès aux deux usines
        // PrereservationFactory et ReservationFactory du modèle qu'on a fabriqué ci-dessus.

        // MaVue vue = new MaVue(bookingPointComAPISeulement)

        // puis démarrer la vue avec une méthode adaptée.
        // vue.run();
        
        System.out.print("Il n'y a pas de vue mais il faudrait le faire ici.\n");

        // Notez que les objets du modèle créés ci-dessus sont tous castés en interfaces de l'API.

        // la vue doit donc utiliser seulement les méthodes publiques de l'API.
        // On peut donc changer l'implémentation du modèle tant qu'on ne change pas l'API en préservant le bon fonctionement de la vue et du controleur.
        // Pour l'instant, nous n'avons ni vue, ni controleur, mais nous pouvons faire semblant en interagissant avec le modèle via l'API. 

        // pour choisir au hasard.
        Random random = new Random();
        
        System.out.print("Simulation manuelle du genre de chose que la vue pourrait faire.\n");
        
        System.out.println("==========================");
        System.out.print("Hello Sir. Je cherche votre préreservation avec référence ZORGLUB\n");
        try{
            Prereservation preresa = bookingPointComAPISeulement.getPrereservation("ZORGLUB");
        }
        catch(IllegalStateException e){
            System.out.print("I am sorry sir, no booking under this reference.\n");
        }
        System.out.println("==========================");
        System.out.print("Hello Madam. Je cherche votre préreservation avec référence 2436-3909-NXLL\n");
        try{
            Prereservation preresa = bookingPointComAPISeulement.getPrereservation("2436-3909-NXLL");
            System.out.print("I found your booking.\n");
            System.out.println(preresa.monPrint());

            Chambre libre=null;
            try{
                libre = grandLivreDOrAPISeulement.getChambre(preresa);
                System.out.print("I have a great room for you.\n");
                System.out.println(libre.monPrint());
            }
            catch(IllegalStateException e){
                System.out.print(e.getMessage());
            }
            try{
                System.out.print("You like this room? Excellent! Let me confirm the reservation for you.\n");
                Reservation resa = grandLivreDOrAPISeulement.createReservation(preresa,libre);
                System.out.println(resa.monPrint());
            }
            catch(IllegalStateException e){
                System.out.print(e.getMessage());
            }
        }
        catch(IllegalStateException e){
            System.out.print("I am sorry Madam, no booking under this reference.\n");
        }
        System.out.println("==========================");
        System.out.print("Hello Madam. Vous avez oubliée votre numéro de préréservation. Ce n'est pas grave, je vais chercher avec votre nom et prénom.\n");
        System.out.print("Marine Carpentier? C-A-R-P-E-N-T-I-E-R? Un instant, je vous prie.\n");
        try{
            Set<Prereservation> preresas = bookingPointComAPISeulement.getPrereservations("Carpentier","Marine");
            System.out.print("I found your bookings.\n");
            for(Prereservation p : preresas){
                System.out.println(p.monPrint());
                Chambre libre = null;
                Set<Chambre> disponibles=null;
                try{
                    disponibles = grandLivreDOrAPISeulement.getChambres(p);
                    System.out.print("I have great rooms for you :\n");
                    for(Chambre c : disponibles){
                        System.out.println(c.monPrint());
                    }
                    // choix de la chambre au hasard simulant le choix du client
                    int choix = random.nextInt(disponibles.size());
                    System.out.println("choix: " + choix);
                    int compter = 0;    
                    for(Chambre c : disponibles){
                        if (compter == choix){
                            libre = c;
                            break;
                        }
                        compter++;
                    }
                }
                catch(IllegalStateException e){
                    System.out.print(e.getMessage());
                }
                try{
                    System.out.println(libre.monPrint());
                    System.out.print("You like this room? Excellent! Let me confirm the reservation for you.\n");
                    Reservation resa = grandLivreDOrAPISeulement.createReservation(p,libre);
                    System.out.println(resa.monPrint());
                }
                catch(IllegalStateException e){
                    System.out.print(e.getMessage());
                }

            }
        }
        catch(IllegalStateException e){
            System.out.print("I am sorry Madam, no booking under this reference.\n");
        }
        System.out.println("==========================");
        System.out.println("=== Vue du manageur   ====");
        System.out.println("==========================");
        Set<Reservation> resas = grandLivreDOrAPISeulement.getReservation(LocalDate.of(2018,01,05));
        System.out.print("Réservations du "+ LocalDate.of(2018,01,07) + ".\n");
        for(Reservation r : resas){
            System.out.println(r.monPrint());
        }

    }
}
