<h2>Connectez-vous</h2>
<?php
		echo form_open('Inscription/connexion',array('method'=>'post','style'=>'text-align:left'));
?>
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
