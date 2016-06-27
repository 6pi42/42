<?php
session_start();
include('verif_admin.php');
?>
<html>
	<head>
		<meta charset="utf-8">
		<link rel="stylesheet" href="style.css">
		<title>Toto-Meubles</title>
	</head>
	<body>
		<form action="create_admin.php" method=post>
			<input class="sub" type="submit" name="submit" value="Creation de compte"/>
		</form>
		<form action="modif_admin.php" method="post">
			<input class="sub" type="submit" name="submit" value="Modification de compte"/>
		</form>
		<form action="suppr_user.php" method="post">
			<input class="sub" type="submit" name="submit" value="Suppression de compte"/>
		</form>
		<form action="add_meuble.php" method="post">
			<input class="sub" type="submit" name="submit" value="Ajout meuble"/>
		</form>
		<a href="index.php">Retour à l'accueil</a>
	</body>
</html>
