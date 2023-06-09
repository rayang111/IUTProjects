package fr.iutfbleau.projetIHM2021FI2.MNP;
import fr.iutfbleau.projetIHM2021FI2.API.*;

import org.mariadb.jdbc.*;
import java.sql.*;
import java.util.*;
import java.time.LocalDate;
import javax.swing.*;

/**
* Une classe pour gérer les bases de données (interne et externe) 
*
*/
public class BaseDonnee{

    /**
    * Un atribut pour gérer la connexion à la base données externe 
    *
    */
    private Connection cnx;
    
    /**
    * Un atribut pour gérer la connexion à la base données interne 
    *
    */
    private Connection cnx2;

    /**
    * Un atribut pour obtenir la référence de la préservation/réservation lors d'une recherche (SELECT)
    *
    */
    private String reference;
    
    /**
    * Un atribut pour obtenir la date du début d'occupation de la préservation/réservation lors d'une recherche (SELECT)
    *
    */
    private LocalDate debut;

    /**
    * Un atribut pour obtenir le nombre de jours de la préservation/réservation lors d'une recherche (SELECT)
    *
    */
    private int jours;

    /**
    * Un atribut pour obtenir la catégorie de la chambre de la préservation/réservation lors d'une recherche (SELECT)
    *
    */
    private TypeChambre categorie;

    /**
    * Un atribut pour obtenir le client de la préservation/réservation lors d'une recherche (SELECT)
    *
    */
    private Client client;
    
    /**
    * Un atribut pour obtenir la référence de la préservation/réservation lors d'une recherche (SELECT)
    *
    */
    private String referenceRecherche;

    /**
    * Un atribut pour obtenir la date du début d'occupation de la préservation/réservation lors d'une recherche (SELECT)
    *
    */
    private LocalDate debutRecherche;
    
    /**
    * Un atribut pour obtenir la date du début d'occupation de la préservation/réservation lors d'une recherche (SELECT)
    *
    */
    private int joursRecherche;

    /**
    * Un atribut pour obtenir la catégorie de la chambre de la préservation/réservation lors d'une recherche (SELECT)
    *
    */    
    private TypeChambre categorieRecherche;

    /**
    * Un atribut pour obtenir le client de la préservation/réservation lors d'une recherche (SELECT)
    *
    */
    private Client clientRecherche;

    /**
    * Un atribut pour obtenir le prénom d'un client de la préservation/réservation lors d'une recherche (SELECT)
    *
    */
    private String prenom;

    /**
    * Un atribut pour obtenir le nom d'un client de la préservation/réservation lors d'une recherche (SELECT)
    *
    */
    private String nom;

    /**
    * Un atribut pour obtenir le prénom d'un client de la préservation/réservation lors d'une recherche (SELECT)
    *
    */
    private String prenomRecherche;

    /**
    * Un atribut pour obtenir le nom d'un client de la préservation/réservation lors d'une recherche (SELECT)
    *
    */
    private String nomRecherche;

    /**
    * Un atribut pour créer une préréservation que l'on pourra renvoyer lors d'une requete.
    *
    */
    private Prereservation prereservation;

    /**
    * Un atribut pour créer un ensemble de préréservations que l'on pourra renvoyer lors d'une requete.
    *
    */
    private Set<Prereservation> prereservations = new HashSet<Prereservation>();

    /**
    * Un atribut pour créer un ensemble réservations que l'on pourra renvoyer lors d'une requete.
    *
    */
    private Set<Reservation> reservation = new HashSet<Reservation>();

    /**
    * Un atribut pour créer une boîte de dialogue notament pour la gestion des erreurs.
    *
    */
    private JOptionPane message = new JOptionPane();

	/**
    * Un constructeur pour se connecter aux bases de données.
    * @throws ClassNotFoundException lors que le pilote de la base de données MariaDB est introuvable
    * @throws SQLException lors d'une erreur de connexion
    */
    public BaseDonnee(){
		try{
			cnx = DriverManager.getConnection("jdbc:mariadb://dwarves.iut-fbleau.fr/projetihm","projetihm", "mhitejorp");
			try{
				Class.forName("org.mariadb.jdbc.Driver");
				System.out.println("Connecté à la base de données externe.");
				try{
					cnx2 = DriverManager.getConnection("jdbc:mariadb://dwarves.iut-fbleau.fr/grib","grib", "grib");
					try{
						Class.forName("org.mariadb.jdbc.Driver");
						System.out.println("Connecté à la base de données interne.");
					} catch(ClassNotFoundException e4){
						System.err.println("Erreur pilote base de données introuvable\n");
                        
                        message.showMessageDialog(null, "Erreur : pilote de la base de données introvable\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
					}
				} catch(SQLException e3){
					System.err.println("Erreur Connection Base de données interne\nVoici plus de détails : \n" + e3);
                    message.showMessageDialog(null, "Erreur : connexion impossible à la base de données interne\n\nDétails : "+e3, "Erreur", JOptionPane.ERROR_MESSAGE);
				}
			} catch(ClassNotFoundException e2){
				System.err.println("Erreur pilote base de données introuvable\n");
                message.showMessageDialog(null, "Erreur : pilote de la base de données introvable\n\nDétails : "+e2, "Erreur", JOptionPane.ERROR_MESSAGE);

			}
		} catch(SQLException e1){
			System.err.println("Erreur Connection Base de données externe\nVoici plus de détails : \n" + e1);
            message.showMessageDialog(null, "Erreur : connexion impossible à la base de données externe\n\nDétails : "+e1, "Erreur", JOptionPane.ERROR_MESSAGE);
		}
	}

    /**
    * Une méthode pour obtenir depuis la base de données externe une préréservation avec une référence donnée de cette dernière
    * @param r reference de type String
    * @return la préréservation trouvée
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
	public Prereservation getPrereservation(String r){
		Objects.requireNonNull(r,"La référence recherchée est null.");
        if(r != null || r != ""){
                this.referenceRecherche = r;
                try{
                    PreparedStatement pst = cnx.prepareStatement("SELECT prenom, nom, debut, nuits, categorie, client FROM Client INNER JOIN Reservation ON Reservation.client = Client.id WHERE reference = ?");
                    pst.setString(1, referenceRecherche);
                    try{
                        ResultSet rs = pst.executeQuery();
                        if(rs == null){
                            System.err.println("Erreur");
                        }   System.out.println("Code : "+r+"\n");   
                            while(rs.next()){
                                prenomRecherche = new String(rs.getString(1));
                                nomRecherche = new String(rs.getString(2));
                                String debutString = rs.getString(3);
                                String[] separDebut = debutString.split("-");
                                debutRecherche = LocalDate.of(Integer.parseInt(separDebut[0]), Integer.parseInt(separDebut[1]), Integer.parseInt(separDebut[2]));
                                joursRecherche = rs.getInt(4);
                                int categorieInt = rs.getInt(5);
                                if(categorieInt == 1){
                                    categorieRecherche = TypeChambre.UNLS;
                                } else if(categorieInt == 2){
                                    categorieRecherche = TypeChambre.DEUXLS;
                                } else if(categorieInt == 3){
                                    categorieRecherche = TypeChambre.UNLD;
                                }
                                clientRecherche = new ClientNP(rs.getInt(6), nomRecherche, prenomRecherche);
                                System.out.println("Résulat : " + referenceRecherche);
                                System.out.println(debutRecherche.toString());
                                System.out.println(Integer.toString(categorieInt));
                                System.out.println(Integer.toString(clientRecherche.getId()));
                                prereservation = new PrereservationNP(referenceRecherche, debutRecherche, joursRecherche,categorieRecherche, clientRecherche);        
                            }
                            rs.close();
                            pst.close();
                            


                    }catch (SQLException e4) {
                        message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);

                    }
            } catch(SQLException e5){
                message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
        }else{
            message.showMessageDialog(null, "Vous n'avez entré aucune valeur", "Erreur",JOptionPane.ERROR_MESSAGE);

        }
        return prereservation;
	}
    /**
    * Une méthode pour obtenir depuis la base de données externe un ensemble de préservations avec un nom et un prénom donnés 
    * @param n nom de type String
    * @param p prénom de type String
    * @return l'ensemble de préréservations trouvée
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
	public Set<Prereservation> getPrereservations(String n, String p){
		Objects.requireNonNull(n,"Le nom recherché est null.");
        Objects.requireNonNull(p,"Le prénom recherché est null.");
        // on va extraire toutes les préréservations du cerveau
        //if (c.isEmpty()){
        //    throw new IllegalStateException("Il n'y a pas de préréservation avec un Client ayant pour nom et prenom : " + n + " et " + p);
        //}
        int i = 0;
        this.prenom = p;
        this.nom = n;
                try{
                    prereservations.clear();
                    PreparedStatement pst = cnx.prepareStatement("SELECT reference, debut, nuits, categorie, client FROM Reservation INNER JOIN Client ON Reservation.client = Client.id WHERE prenom = ? AND nom = ?");
                    pst.setString(1, prenom);
                    pst.setString(2, nom);
                    try{
                        ResultSet rs = pst.executeQuery();
                        if(rs == null){
                            System.err.println("Erreur");
                        }          
                            while(rs.next()){
                                reference = new String(rs.getString(1));
                                String debutString = rs.getString(2);
                                String[] separDebut = debutString.split("-");
                                debut = LocalDate.of(Integer.parseInt(separDebut[0]), Integer.parseInt(separDebut[1]), Integer.parseInt(separDebut[2]));
                                jours = rs.getInt(3);
                                int categorieInt = rs.getInt(4);
                                if(categorieInt == 1){
                                    categorie = TypeChambre.UNLS;
                                } else if(categorieInt == 2){
                                    categorie = TypeChambre.DEUXLS;
                                } else if(categorieInt == 3){
                                    categorie = TypeChambre.UNLD;
                                }
                                client = new ClientNP(rs.getInt(5), nom, prenom);
                                prereservations.add(new PrereservationNP(reference, debut, jours, categorie, client));          
                            }
                            rs.close();
                            pst.close();
                            


                    }catch (SQLException e4) {
                        message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
                    }
            } catch(SQLException e5){
                message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
        return prereservations;
	}


    /**
    * Une méthode pour créer dans la base de données interne une réservation
    * @param p préréservation
    * @param c chambre 
    * @return la réservation créée
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
	public Reservation creerReservation(Prereservation p, Chambre c){
		try{
			PreparedStatement pst = cnx2.prepareStatement("INSERT INTO Reservation (reference, dateDebut, jours, chambre, client) VALUES (?, ?, ?, ?, ?)");
			pst.setString(1, p.getReference());
			pst.setDate(2, java.sql.Date.valueOf(p.getDateDebut()));
			pst.setInt(3, p.getJours());
			pst.setInt(4, c.getNumero());
			pst.setInt(5, p.getClient().getId());
			pst.executeUpdate();
			pst.close();
		} catch(SQLException e5){
                message.showMessageDialog(null, "Erreur SQL: client déjà ajouté\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
        }
		return new ReservationNP(p.getReference(), p.getDateDebut(), p.getJours(), c, p.getClient());
	}

    /**
    * Une méthode pour compter le nombre de chambre dans la base de données interne
    * @return le nombre de chambre 
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
	public int getNombreChambre(){
		int nombreChambre = 0;
                try{
                    PreparedStatement pst = cnx2.prepareStatement("SELECT COUNT(*) FROM Chambre");
                    try{
                        ResultSet rs = pst.executeQuery();
                        if(rs == null){
                            System.err.println("Erreur");
                        }          
                            while(rs.next()){
       							nombreChambre = rs.getInt(1);
                            }
                            rs.close();
                            pst.close();
                            


                    }catch (SQLException e4) {
                        message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
                    }
            } catch(SQLException e5){
                message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
            return nombreChambre;		
	}

    /**
    * Une méthode pour obtenir depuis la base de données interne le nombre de chambre disponibles
    * @param d date au quel on veut avoir des données
    * @return le nombre de chambres
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
	public int getDisponibles(LocalDate d){
		int nombreDisponibles = 0;
                try{
                    PreparedStatement pst = cnx2.prepareStatement("SELECT COUNT(*) FROM Chambre INNER JOIN Reservation ON Chambre.numero = Reservation.chambre WHERE ? BETWEEN Reservation.dateDebut AND DATE_ADD(dateDebut, INTERVAL jours DAY)");
                    pst.setDate(1, java.sql.Date.valueOf(d));
                    try{
                        ResultSet rs = pst.executeQuery();
                        if(rs == null){
                            System.err.println("Erreur");
                        }          
                            while(rs.next()){
       							nombreDisponibles = rs.getInt(1);

                            }
                            rs.close();
                            pst.close();
                            


                    }catch (SQLException e4) {
                        message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
                    }
            } catch(SQLException e5){
                message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
            return nombreDisponibles;		
	}


    /**
    * Une méthode pour obtenir depuis la base de données interne le nombre de chambre disponibles
    * @param d1 date début
    * @param d2 date fin
    * @return le nombre de chambres
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
    public int getDisponibles(LocalDate d1, LocalDate d2){
        int nombreDisponibles = 0;
                try{
                    PreparedStatement pst = cnx2.prepareStatement("SELECT COUNT(*) FROM Chambre INNER JOIN Reservation ON Chambre.numero = Reservation.chambre WHERE Reservation.dateDebut BETWEEN ? AND ?");
                    pst.setDate(1, java.sql.Date.valueOf(d1));
                    pst.setDate(2, java.sql.Date.valueOf(d2));
                    try{
                        ResultSet rs = pst.executeQuery();
                        if(rs == null){
                            System.err.println("Erreur");
                        }          
                            while(rs.next()){
                                nombreDisponibles = rs.getInt(1);

                            }
                            rs.close();
                            pst.close();
                            


                    }catch (SQLException e4) {
                        message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
                    }
            } catch(SQLException e5){
                message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
            return nombreDisponibles;       
    }

    /**
    * Une méthode pour obtenir depuis la base de données interne le nombre de chambre disponibles
    * @param d date au quel on veut avoir des données
    * @param t type de chambre
    * @return le nombre de chambres
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
    public int getDisponibles(LocalDate d, TypeChambre t){
        int nombreDisponibles = 0;
                try{
                    PreparedStatement pst = cnx2.prepareStatement("SELECT COUNT(*) FROM Chambre INNER JOIN Reservation ON Chambre.numero = Reservation.chambre WHERE ? BETWEEN Reservation.dateDebut AND DATE_ADD(dateDebut, INTERVAL jours DAY) AND chambre = ?");
                    pst.setDate(1, java.sql.Date.valueOf(d));
                    int categorieRecherche = 0;
                    if(t == TypeChambre.UNLS){
                        categorieRecherche = 1;
                    } else if(t == TypeChambre.DEUXLS){
                        categorieRecherche = 2;
                    } else if(t == TypeChambre.UNLD){
                        categorieRecherche = 3;
                    }
                    pst.setInt(2, categorieRecherche);
                    try{
                        ResultSet rs = pst.executeQuery();
                        if(rs == null){
                            System.err.println("Erreur");
                        }          
                            while(rs.next()){
                                nombreDisponibles = rs.getInt(1);

                            }
                            rs.close();
                            pst.close();
                            


                    }catch (SQLException e4) {
                        message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
                    }
            } catch(SQLException e5){
                message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
            return nombreDisponibles;       
    }

    /**
    * Une méthode pour obtenir depuis la base de données interne le nombre moyen de chambre disponibles
    * @param d1 date début
    * @param d2 date fin
    * @param t Type de chambre
    * @return le nombre moyen de chambres
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
    public int getDisponibles(LocalDate d1, LocalDate d2, TypeChambre t){
        int nombreDisponibles = 0;
        int somme = 0;
        int total = 0;
        int categorieRechercheT = 0;
            try{
                PreparedStatement pst = cnx2.prepareStatement("SELECT COUNT(*) FROM Chambre WHERE categorie = ?");
                if(t == TypeChambre.UNLS){
                        categorieRechercheT = 1;
                    } else if(t == TypeChambre.DEUXLS){
                        categorieRechercheT = 2;
                    } else if(t == TypeChambre.UNLD){
                        categorieRechercheT = 3;
                    }
                pst.setInt(1, categorieRechercheT);
                try{
                    ResultSet rs = pst.executeQuery();
                    if(rs == null){
                        System.err.println("Erreur");
                    }          
                        while(rs.next()){
                            total = rs.getInt(1);
                        }
                        rs.close();
                        pst.close();                           

                    }catch (SQLException e4) {
                        message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
                    }                    
                } catch(SQLException e5){
                    message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
                } 
                try{
                    PreparedStatement pst = cnx2.prepareStatement("SELECT COUNT(*) FROM Chambre INNER JOIN Reservation ON Chambre.numero = Reservation.chambre WHERE categorie = ? AND dateDebut BETWEEN ? AND ?");
                    if(t == TypeChambre.UNLS){
                        categorieRechercheT = 1;
                    } else if(t == TypeChambre.DEUXLS){
                        categorieRechercheT = 2;
                    } else if(t == TypeChambre.UNLD){
                        categorieRechercheT = 3;
                    }
                    pst.setInt(1, categorieRechercheT);
                    pst.setDate(2, java.sql.Date.valueOf(d1));
                    pst.setDate(3, java.sql.Date.valueOf(d2));
                    try{
                        ResultSet rs = pst.executeQuery();
                        if(rs == null){
                            System.err.println("Erreur");
                        }          
                            while(rs.next()){
                                somme = rs.getInt(1);
                                System.err.println(somme);

                            }
                            rs.close();
                            pst.close();
                            



            } catch(SQLException e6) {
                        message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e6, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
            } catch(SQLException e5){
                    message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
            }  

            return somme/total;       
    }

    /**
    * Une méthode pour obtenir depuis la base de données interne les chambres disponibles
    * @param t Type de chambre voulu
    * @return l'ensemble de chambre disponibles 
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
	public Set<Chambre> getChambreLibres(TypeChambre t){
		Set<Chambre> chambreDisponibles = new HashSet<Chambre>();
		    try{
                PreparedStatement pst = cnx2.prepareStatement("SELECT numero, categorie FROM Chambre WHERE numero NOT IN (SELECT numero FROM Chambre INNER JOIN Reservation ON Reservation.chambre = Chambre.numero) AND categorie = ?");
                int categorieRecherche = 0;
                if(t == TypeChambre.UNLS){
                    categorieRecherche = 1;
                } else if(t == TypeChambre.DEUXLS){
                    categorieRecherche = 2;
                } else if(t == TypeChambre.UNLD){
                    categorieRecherche = 3;
                }
                pst.setInt(1, categorieRecherche);
                try{
                    ResultSet rs = pst.executeQuery();
                    if(rs == null){
                        System.err.println("Erreur");
                    }          
                    while(rs.next()){
                    	int categorieInt = rs.getInt(2);
                        if(categorieInt == 1){
                            categorie = TypeChambre.UNLS;
                        } else if(categorieInt == 2){
                            categorie = TypeChambre.DEUXLS;
                        } else if(categorieInt == 3){
                            categorie = TypeChambre.UNLD;
                        }
       					chambreDisponibles.add(new ChambreNP(rs.getInt(1), categorie));
                    }
                	rs.close();
                    pst.close();        

            }catch (SQLException e4) {
                message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
        } catch(SQLException e5){
            message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
        }
		return chambreDisponibles;
	}

    /**
    * Une méthode pour obtenir depuis la base de données interne les réservations
    * @param d à une certaine date
    * @return l'ensemble de réservations 
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
	public Set<Reservation> getReservation(LocalDate d){
		Objects.requireNonNull(d,"La référence recherchée est null.");
        if(d != null){
                reservation.clear();
                try{
                    PreparedStatement pst = cnx2.prepareStatement("SELECT reference, dateDebut, jours, categorie, chambre, client FROM Reservation INNER JOIN Chambre ON Reservation.chambre = Chambre.numero WHERE  dateDebut= ?");
                    pst.setDate(1, java.sql.Date.valueOf(d));
                    try{
                        ResultSet rs = pst.executeQuery();
                        if(rs == null){
                            System.err.println("Erreur");
                        }
                            while(rs.next()){
                                String reference = new String(rs.getString(1));
                                String debutString = rs.getString(2);
                                String[] separDebut = debutString.split("-");
                                LocalDate debutRecherche = LocalDate.of(Integer.parseInt(separDebut[0]), Integer.parseInt(separDebut[1]), Integer.parseInt(separDebut[2]));
                                int joursRecherche = rs.getInt(3);
                                int categorieInt = rs.getInt(4);
                                if(categorieInt == 1){
                                    categorieRecherche = TypeChambre.UNLS;
                                } else if(categorieInt == 2){
                                    categorieRecherche = TypeChambre.DEUXLS;
                                } else if(categorieInt == 3){
                                    categorieRecherche = TypeChambre.UNLD;
                                }
                                int chambreNum = rs.getInt(5);
                                int id = rs.getInt(6);
                                String prenom = "";
                                String nom = "";
                                try{
                    				PreparedStatement pst2 = cnx.prepareStatement("SELECT prenom, nom FROM Client WHERE  id= ?");
                    				pst2.setInt(1, id);
                    				try{
                    					ResultSet rs2 = pst2.executeQuery();
                    					while(rs2.next()){
                    						prenom = rs2.getString(1);
                    						nom = rs2.getString(2);
                    					}
                    					rs2.close();
                    					pst2.close();
                    				}catch(SQLException e6){
                    					message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e6, "Erreur", JOptionPane.ERROR_MESSAGE);
                    				}                               	
                                }catch(SQLException e7){
                                	message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e7, "Erreur", JOptionPane.ERROR_MESSAGE);
                                }
                                client = new ClientNP(id, nom, prenom);
                                Chambre chambre = new ChambreNP(chambreNum, categorieRecherche);
                                reservation.add( new ReservationNP(reference, debutRecherche, joursRecherche, chambre, client));   
                            }
                            rs.close();
                            pst.close();
                            


                    }catch (SQLException e4) {
                        message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
                    }
            } catch(SQLException e5){
                message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
        }else{
            message.showMessageDialog(null, "Vous n'avez entré aucune valeur", "Erreur",JOptionPane.ERROR_MESSAGE);

        }
        return reservation;
	}

    /**
    * Une méthode pour obtenir depuis la base de données interne les réservations
    * @param d à une certaine date
    * @param t d'un certain type de chambre
    * @return l'ensemble de réservations 
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
	public Set<Reservation> getReservation(LocalDate d, TypeChambre t){
		Objects.requireNonNull(d,"La référence recherchée est null.");
        if(d != null){
                reservation.clear();
                try{
                    PreparedStatement pst = cnx2.prepareStatement("SELECT reference, dateDebut, jours, categorie, chambre, client FROM Reservation INNER JOIN Chambre ON Reservation.chambre = Chambre.numero WHERE  dateDebut= ? AND chambre= ?");
                    pst.setDate(1, java.sql.Date.valueOf(d));
                    int categorieRechercheI = 0;
					if(t == TypeChambre.UNLS){
	                    categorieRechercheI = 1;
	                } else if(t == TypeChambre.DEUXLS){
	                    categorieRechercheI = 2;
	                } else if(t == TypeChambre.UNLD){
	                    categorieRechercheI = 3;
	                }                  
                    pst.setInt(2, categorieRechercheI);
                    try{
                        ResultSet rs = pst.executeQuery();
                        if(rs == null){
                            System.err.println("Erreur");
                        }
                            while(rs.next()){
                                String reference = new String(rs.getString(1));
                                String debutString = rs.getString(2);
                                String[] separDebut = debutString.split("-");
                                LocalDate debutRecherche = LocalDate.of(Integer.parseInt(separDebut[0]), Integer.parseInt(separDebut[1]), Integer.parseInt(separDebut[2]));
                                int joursRecherche = rs.getInt(3);
                                int categorieInt = rs.getInt(4);
                                if(categorieInt == 1){
                                    categorieRecherche = TypeChambre.UNLS;
                                } else if(categorieInt == 2){
                                    categorieRecherche = TypeChambre.DEUXLS;
                                } else if(categorieInt == 3){
                                    categorieRecherche = TypeChambre.UNLD;
                                }
                                int chambreNum = rs.getInt(5);
                                int id = rs.getInt(6);
                                String prenom = "";
                                String nom = "";
                                try{
                    				PreparedStatement pst2 = cnx.prepareStatement("SELECT prenom, nom FROM Client WHERE  id= ?");
                    				pst2.setInt(1, id);
                    				try{
                    					ResultSet rs2 = pst2.executeQuery();
                    					while(rs2.next()){
                    						prenom = rs2.getString(1);
                    						nom = rs2.getString(2);
                    					}
                    					rs2.close();
                    					pst2.close();
                    				}catch(SQLException e6){
                    					message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e6, "Erreur", JOptionPane.ERROR_MESSAGE);
                    				}                               	
                                }catch(SQLException e7){
                                	message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e7, "Erreur", JOptionPane.ERROR_MESSAGE);
                                }
                                client = new ClientNP(id, nom, prenom);
                                Chambre chambre = new ChambreNP(chambreNum, categorieRecherche);
                                reservation.add( new ReservationNP(reference, debutRecherche, joursRecherche, chambre, client));   
                            }
                            rs.close();
                            pst.close();
                            


                    }catch (SQLException e4) {
                        message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
                    }
            } catch(SQLException e5){
                message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
        }else{
            message.showMessageDialog(null, "Vous n'avez entré aucune valeur", "Erreur",JOptionPane.ERROR_MESSAGE);

        }
        return reservation;
	}


    /**
    * Une méthode pour obtenir depuis la base de données interne les réservations
    * @param d1 depuis une certaine date
    * @param d2 jusqu'à une autre date
    * @param t d'un certain type de chambre
    * @return l'ensemble de réservations 
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
    public Set<Reservation> getReservation(LocalDate d1, LocalDate d2, TypeChambre t){
        Objects.requireNonNull(d1,"La référence recherchée est null.");
        Objects.requireNonNull(d2,"La référence recherchée est null.");
        Objects.requireNonNull(t,"La référence recherchée est null.");
        if(d1 != null || d2 != null || t != null){
                reservation.clear();
                try{
                    PreparedStatement pst = cnx2.prepareStatement("SELECT reference, dateDebut, jours, categorie, chambre, client FROM Reservation INNER JOIN Chambre ON Reservation.chambre = Chambre.numero WHERE  (dateDebut BETWEEN ? AND ?) AND chambre= ?");
                    pst.setDate(1, java.sql.Date.valueOf(d1));
                    pst.setDate(2, java.sql.Date.valueOf(d2));
                    int categorieRechercheI = 0;
                    if(t == TypeChambre.UNLS){
                        categorieRechercheI = 1;
                    } else if(t == TypeChambre.DEUXLS){
                        categorieRechercheI = 2;
                    } else if(t == TypeChambre.UNLD){
                        categorieRechercheI = 3;
                    }                  
                    pst.setInt(3, categorieRechercheI);
                    try{
                        ResultSet rs = pst.executeQuery();
                        if(rs == null){
                            System.err.println("Erreur");
                        }
                            while(rs.next()){
                                String reference = new String(rs.getString(1));
                                String debutString = rs.getString(2);
                                String[] separDebut = debutString.split("-");
                                LocalDate debutRecherche = LocalDate.of(Integer.parseInt(separDebut[0]), Integer.parseInt(separDebut[1]), Integer.parseInt(separDebut[2]));
                                int joursRecherche = rs.getInt(3);
                                int categorieInt = rs.getInt(4);
                                if(categorieInt == 1){
                                    categorieRecherche = TypeChambre.UNLS;
                                } else if(categorieInt == 2){
                                    categorieRecherche = TypeChambre.DEUXLS;
                                } else if(categorieInt == 3){
                                    categorieRecherche = TypeChambre.UNLD;
                                }
                                int chambreNum = rs.getInt(5);
                                int id = rs.getInt(6);
                                String prenom = "";
                                String nom = "";
                                try{
                                    PreparedStatement pst2 = cnx.prepareStatement("SELECT prenom, nom FROM Client WHERE  id= ?");
                                    pst2.setInt(1, id);
                                    try{
                                        ResultSet rs2 = pst2.executeQuery();
                                        while(rs2.next()){
                                            prenom = rs2.getString(1);
                                            nom = rs2.getString(2);
                                        }
                                        rs2.close();
                                        pst2.close();
                                    }catch(SQLException e6){
                                        message.showInputDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e6, "Erreur", JOptionPane.ERROR_MESSAGE);
                                    }                                   
                                }catch(SQLException e7){
                                    message.showInputDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e7, "Erreur", JOptionPane.ERROR_MESSAGE);
                                }
                                client = new ClientNP(id, nom, prenom);
                                Chambre chambre = new ChambreNP(chambreNum, categorieRecherche);
                                reservation.add( new ReservationNP(reference, debutRecherche, joursRecherche, chambre, client));   
                            }
                            rs.close();
                            pst.close();
                            


                    }catch (SQLException e4) {
                        message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
                    }
            } catch(SQLException e5){
                message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
        }else{
            message.showMessageDialog(null, "Vous n'avez entré aucune valeur", "Erreur",JOptionPane.ERROR_MESSAGE);

        }
        return reservation;        
    }

    /**
    * Une méthode pour obtenir depuis la base de données interne le ratio de chambre occupées
    * @param d à une certaine date
    * @return le pourcentage obtenu
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
    public int getRatio(LocalDate d){
        int count = 0;
        try{
            PreparedStatement pst = cnx.prepareStatement("SELECT COUNT(*) FROM Reservation INNER JOIN Client ON Reservation.client = Client.id WHERE ? BETWEEN debut AND DATE_ADD(debut, INTERVAL nuits DAY)");
            pst.setDate(1, java.sql.Date.valueOf(d));
            try{
                ResultSet rs = pst.executeQuery();
                if(rs == null){
                    System.err.println("Erreur");
               } 
               System.out.println("Code : "+d+"\n");   
                while(rs.next()){
                    count = rs.getInt(1);
                    System.out.println(count);                                          
                }            
            }catch (SQLException e4) {
                message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
        } catch(SQLException e5){
            message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
        }        
        return count;
    }

    /**
    * Une méthode pour obtenir depuis la base de données interne le ratio de chambre occupées
    * @param d à une certaine date
    * @param t d'un certain type de chambre
    * @return le pourcentage obtenu
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
    public int getRatio(LocalDate d, TypeChambre t){
        int count = 0;
        try{
            PreparedStatement pst = cnx.prepareStatement("SELECT COUNT(*) FROM Reservation INNER JOIN Client ON Reservation.client = Client.id WHERE ? BETWEEN debut AND DATE_ADD(debut, INTERVAL nuits DAY) AND categorie = ?");
            pst.setDate(1, java.sql.Date.valueOf(d));
            int categorieRechercheI = 0;
            if(t == TypeChambre.UNLS){
               categorieRechercheI = 1;
            } else if(t == TypeChambre.DEUXLS){
                categorieRechercheI = 2;
            } else if(t == TypeChambre.UNLD){
                categorieRechercheI = 3;
            }                  
            pst.setInt(2, categorieRechercheI);            
            try{
                ResultSet rs = pst.executeQuery();
                if(rs == null){
                    System.err.println("Erreur");
               } 
               System.out.println("Code : "+d+"\n");   
                while(rs.next()){
                    count = rs.getInt(1);
                    System.out.println(count);                                          
                }            
            }catch (SQLException e4) {
                message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
        } catch(SQLException e5){
            message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
        }        
        return count;
    }

    /**
    * Une méthode pour obtenir depuis la base de données interne le ratio de chambre occupées
    * @param d1 à partir d'une certaine date
    * @param d2 jusqu'à une certaine date
    * @return le pourcentage obtenu
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
    public int getRatio(LocalDate d1, LocalDate d2){
        int count = 0;
        try{
            PreparedStatement pst = cnx.prepareStatement("SELECT COUNT(*) FROM Reservation INNER JOIN Client ON Reservation.client = Client.id WHERE debut BETWEEN ? AND ?");
            pst.setDate(1, java.sql.Date.valueOf(d1));
            pst.setDate(2, java.sql.Date.valueOf(d2));          
            try{
                ResultSet rs = pst.executeQuery();
                if(rs == null){
                    System.err.println("Erreur");
               } 
                while(rs.next()){
                    count = rs.getInt(1);
                    System.out.println(count);                                          
                }            
            }catch (SQLException e4) {
                message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
        } catch(SQLException e5){
            message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
        }        
        return count;
    }

    /**
    * Une méthode pour obtenir depuis la base de données interne le ratio de chambre occupées
    * @param d1 à partir d'une certaine date
    * @param d2 jusqu'à une certaine date
    * @param t d'un certain type de chambre
    * @return le pourcentage obtenu
    * @throws SQLException lors d'une erreur de requete avec un message d'erreur affiché à l'écran
    */
    public int getRatio(LocalDate d1, LocalDate d2, TypeChambre t){
        int count = 0;
        try{
            PreparedStatement pst = cnx.prepareStatement("SELECT COUNT(*) FROM Reservation INNER JOIN Client ON Reservation.client = Client.id WHERE debut BETWEEN ? AND ? AND categorie = ?");
            pst.setDate(1, java.sql.Date.valueOf(d1));
            pst.setDate(2, java.sql.Date.valueOf(d2));
            int categorieRechercheI = 0;
            if(t == TypeChambre.UNLS){
               categorieRechercheI = 1;
            } else if(t == TypeChambre.DEUXLS){
                categorieRechercheI = 2;
            } else if(t == TypeChambre.UNLD){
                categorieRechercheI = 3;
            }                  
            pst.setInt(3, categorieRechercheI);           
            try{
                ResultSet rs = pst.executeQuery();
                if(rs == null){
                    System.err.println("Erreur");
               } 
                while(rs.next()){
                    count = rs.getInt(1);
                    System.out.println(count);                                          
                }            
            }catch (SQLException e4) {
                message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e4, "Erreur", JOptionPane.ERROR_MESSAGE);
            }
        } catch(SQLException e5){
            message.showMessageDialog(null, "Erreur SQL: lors de la recherche\n\nDétails : "+e5, "Erreur", JOptionPane.ERROR_MESSAGE);
        }        
        return count;
    }


}