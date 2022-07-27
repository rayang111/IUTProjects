	<div id="body">
		<p>Créez un sondage.</p>
		<p>Suivez les instructions suit dessous</p>
		<?php
			echo "$cle"; 
		?>
		<?php
		echo form_open('Accueil/redirection',array('method'=>'get','style'=>'text-align:left'));
			echo form_submit('','Retour');
			echo form_close();		
		?>
	</div>

</body>