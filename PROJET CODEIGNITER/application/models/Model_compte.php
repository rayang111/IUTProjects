<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');


class Model_compte extends CI_Model {

	public $idComtpe;
	public $login = "";
	public $password = "";
	public $email = "";

	public function __construct(){
	$this->load->database();
	}


	function create_compte($data) {
		$options = [
			'cost' => 12,
		];
		$data['password'] = password_hash($data['password'], PASSWORD_BCRYPT, $options);
		return $this->db->insert('Compte', $data);
	}

	function check_password($login, $password) {

		$query = $this->db->query("SELECT login,password FROM Compte WHERE login='$login';");
		$row = $query->row();

		foreach ($query->result_array() as $row) {
		}

		if($row==null) {		
			return false;
		} else if(!password_verify($password, $row['password'])) {
			return false;
		} else {
			return true;
		}
	}


	function getCompte($login) {
		$query = $this->db->query("SELECT idCompte,login,nom,prenom,password,email FROM Compte WHERE login='$login';");
		$row = $query->row();

		foreach ($query->result_array() as $row) {
		}

		return $row;
	}

}
?>