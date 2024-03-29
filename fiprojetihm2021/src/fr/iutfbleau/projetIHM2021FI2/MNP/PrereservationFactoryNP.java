package fr.iutfbleau.projetIHM2021FI2.MNP;
import fr.iutfbleau.projetIHM2021FI2.API.*;
import java.time.LocalDate;
import java.util.*;
import java.util.function.Predicate;
import org.mariadb.jdbc.*;
import java.sql.*;
/**
 *  Usine non persistante stockant les préréservation dans une structure de donnée permettant de simuler un ensemble.
 * 
 *  Elle permet de rechercher les préréservations à partir du numéro d'une préréservation, ou bien du nom et prenom d'un Client.
 *
 * La recherche par numéro devrait être plus efficace.
 *
 */
public class PrereservationFactoryNP implements PrereservationFactory{
    
    // plutôt que d'utiliser un ensemble, on utilise un HashMap car on suppose qu'on va devoir chercher
    // plutôt les préréservations avec le numéro de référence (un String, voir Prereservation).
    // Pour la recherche par nom et prenom on va devoir traverser le HashMap.
    private HashMap<String,Prereservation> brain =new HashMap<String,Prereservation>();//Creating HashMap


    private BaseDonnee bd;

     /**
      * Constructeur
      */
     public PrereservationFactoryNP(BaseDonnee bd){
        this.bd = bd;     
     }

    /**
     * Recherche une préréservation par reference
     * @param  r la référence du système de préréservation 
     * @return la préréservation.
     * @throws NullPointerException si un argument est null
     * @throws IllegalStateException si la Préréservation avec cette référence n'existe pas.
     *
     * Ne devrait pas retourner un objet null.
     */
    public Prereservation getPrereservation(String r){
        return this.bd.getPrereservation(r);

    }
    /**
     * Recherche une préréservation par nom et prenom
     * @param  n le nom
     * @param  p le prenom
     * @return un ensemble de préréservations.
     * @throws NullPointerException si un argument est null
     * @throws IllegalStateException si aucune préréservation n'existe avec ce nom
     *
     * Ne devrait pas retourner un objet null ou un ensemble vide.
     */
    public Set<Prereservation> getPrereservations(String n, String p){
        return this.bd.getPrereservations(n, p);
        // on fabrique un ensemble.
        //Set<Prereservation> found = new HashSet<Prereservation>(c);
        //return found;
    }


    // NB : jusqu'ici on ne dépend pas d'un choix particulier de Prereservation.
    //      La méthode ci-dessous utilise (de manière très marginale) PrereservationNP
    //      Elle assure que le cerveau (this.brain) contient au plus une prereservation pour une reference

    /**
     * Utile pour faire des tests avec cette classe.
     * A priori ne sert pas si on fait une version persistante 
     * @throws IllegalStateException si on connaît déjà une préréservation avec cette référence.
     * @throws NullPointerException si un argument est null
     * @throws IllegalArgumentException si jours < 1
     */
    public void ajoutePrereservation(String reference, LocalDate dateDebut, int jours, TypeChambre t, Client client){
        if (this.brain.containsKey(reference)){
            throw new IllegalStateException("Il y a déjà une préréservation avec cette référence : " + reference);
        }
        else {
            Prereservation preresa = new PrereservationNP(reference, dateDebut, jours, t, client);
            this.brain.put(reference,preresa);
        }
    }
}
 
 
