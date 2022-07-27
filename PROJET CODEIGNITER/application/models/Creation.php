<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Creation extends CI_Model {

	public function __construct(){
		$this->load->database();
	}
		public function creer_compte(){
			$nom=$_POST['nom'];
			$prenom= $_POST['prenom'];
			$mdp=$_POST['mdp'];
			$email=$_POST['email'];
			$hash=password_hash($mdp, PASSWORD_BCRYPT);
			echo"$hash";
			$link=mysqli_connect("localhost","grib","grib","grib");
			if(!$link){
			die("<p>connexion impossible</p>('. mysqli_connect_errno() .')'. mysqli_connect_error()");
			}
			$ajout=mysqli_query($link, "INSERT INTO User VALUES('$nom','$prenom','$hash','$email')");
			if($ajout){
				echo "Inscription effectuée.";
			}

		}

		public function connection_compte(){
			$mdp=$_POST['mdp'];
			$email=$_POST['email'];
			$link=mysqli_connect("localhost","grib","grib","grib");
			if(!$link){
			die("<p>connexion impossible</p>('. mysqli_connect_errno() .')'. mysqli_connect_error()");
			}
			$mail=mysqli_query($link,"SELECT email FROM User WHERE email = '$email'");
			$pwd=mysqli_query($link,"SELECT email, mdp FROM User WHERE email = '$email'");
			if($mail){
				foreach ($mail as $row) {
					if($row==$mail['email']){
						echo "correct";
					}
				}

			}

		}
	}
?>

