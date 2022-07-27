<!DOCTYPE html>
<html>
<head>
	<title>inscription</title>
</head>
<body>



	<?php

$mdp=$_POST['mdp'];
$email=$_POST['email'];
$link=mysqli_connect("localhost","benrejeb","benrejeb","benrejeb");
if(!$link){
die("<p>connexion impossible</p>");
}
$mail=mysqli_query($link,"SELECT email FROM User");
$pwd=mysqli_query($link,"SELECT mdp FROM User");
if ($mdp==$pwd && $email==$mail) {
	echo "nice";
} else {
	echo"olala";
}
?>
</body>
</html>
