<?php
defined('BASEPATH') OR exit('No direct script access allowed');

class Inscription extends CI_Controller {

	public function creer_compte(){
 		$this->load->helper('form');
		$this->load->library('form_validation');

		$this->form_validation->set_rules('nom', 'nom', 'required');
		$this->form_validation->set_rules('prenom', 'prenom', 'required');
		$this->form_validation->set_rules('email', 'Email', 'required');

		$this->form_validation->set_message('is_unique', '{field} est déjà présent dans la base.');

		$this->load->view('header');
		$this->load->view('formulaire');
		$this->load->view('footer');
	}

	public function creation(){
		$this->load->model('creation');
		$this->creation->creer_compte();
	}

	public function se_connecter(){
		$this->load->helper('form');
		$this->load->library('form_validation');
		$this->form_validation->set_rules('email', 'Email', 'required');
		$this->load->view('header');
		$this->load->view('conform');
		$this->load->view('footer');
	}

	public function connexion(){
		$this->load->model('creation');
		$this->creation->connection_compte();
		

	}
}
