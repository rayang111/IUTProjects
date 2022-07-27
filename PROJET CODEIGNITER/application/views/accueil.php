
	<div id="body">
		<p>Bienvenue sur Meet-us.</p>
		<p>Rejoinez notre plateforme de sondage en ligne !</p>
		<?php
			echo form_open('Inscription/creer_compte',array('method'=>'get','style'=>'text-align:left'));
			echo form_submit('','Inscription');
			echo form_close();		
		?>
		<?php
			echo form_open('Inscription/se_connecter',array('method'=>'get','style'=>'text-align:left'));
			echo form_submit('','Connexction');
			echo form_close();		
		?>
		<?php
		echo form_open('Sondage/creer_sondage',array('method'=>'get','style'=>'text-align:left'));
			echo form_submit('','Créer un sondage');
			echo form_close();		
		?>
	</div>

</body>
