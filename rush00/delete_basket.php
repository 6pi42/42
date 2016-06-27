<?php 
	session_start();
	$_SESSION['tot'] = 0;
	$_SESSION['elmt'] = 0;
	$_SESSION['basket'] = array();
	header('Location: panier.php');
?>
