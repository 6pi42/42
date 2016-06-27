<?php
	session_start();
	include('config.php');
	$mysqli = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass, $mysqli_db);
	$basket = $_SESSION['basket'];
	$loggued = $_SESSION['loggued_as'];
	$str = serialize($basket);
	if ($loggued) {
		$req = "SELECT * FROM `panier` WHERE username='$loggued';";
		$data = mysqli_query($mysqli, $req);
		if (mysqli_num_rows($data)) {
			$req = "DELETE FROM `panier` WHERE username='$loggued';";
			$data = mysqli_query($mysqli, $req);
		}
		$req = "INSERT INTO `panier`(`username`, `data`) VALUES ('$loggued', '$str');";
		$data = mysqli_query($mysqli, $req);
		header('Location: panier.php');
	}
	else {
		echo "<script type='text/javascript'>alert('Veuillez vous enregistrez');window.location = 'panier.php';</script>";
	}
?>
