<?php
$nom=$_POST['nom'];
$prenom= $_POST['prenom'];
$mdp=$_POST['mdp'];
$email=$_POST['email'];
$link=mysqli_connect("localhost","benrejeb","benrejeb","benrejeb");
if(!$link){
die("<p>connexion impossible</p>");
}
mysqli_query($link, "INSERT INTO User VALUES('$nom','$prenom','$mdp','$email')");

?>