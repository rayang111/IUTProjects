<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');


class Model_sondage extends CI_Model {

	public function generation_cle(){
		return md5(uniqid(rand(), true));
	}
	

}