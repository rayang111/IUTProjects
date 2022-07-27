<?php echo validation_errors(); ?>
<h2>Incrivez-vous dès maintenant</h2>
<?php
		echo form_open('Inscription/creation',array('method'=>'post','style'=>'text-align:left'));
?>
	<p>Votre nom : <input type="text" name="nom" /></p>
	<p>Votre prenom : <input type="text" name="prenom" /></p>
	<p>Votre email : <input type="text" name="email" /></p>
	<p>Votre password : <input type="password" name="mdp" /></p>
<?php
			echo form_submit('','Envoyer');
			echo form_close();		
?>

<?php
		echo form_open('Accueil/redirection',array('method'=>'get','style'=>'text-align:left'));
			echo form_submit('','Retour');
			echo form_close();		
?>

</body>
