<?php
session_start();
include'config.php';
if (!isset($_SESSION['DB'])) {
	include 'install.php';
	$_SESSION['DB'] = 1;
}



if (!$mysqli = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass, $mysqli_db))
{
	echo "Database connection failed";
}
?>
<html>
	<head>
		<title>Meubles</title>
		<link rel="stylesheet" type="text/css" href="style.css">
	</head>
	<body>
		<a href="index.php"><div class="banner">Toto-Meubles</div></a>
		<div class="leftmodule1">
<?php
if (isset($_SESSION['loggued_as'])) {
	$con = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass, $mysqli_db);
	if (mysqli_connect_errno()) {
		echo "Failed to connect to MySQL: " . mysqli_connect_error();
	}
	else {
		$stmt = mysqli_prepare($con, "SELECT username,classe FROM users WHERE username=? AND classe='3';");
		mysqli_stmt_bind_param($stmt, "s", $_SESSION['loggued_as']);
		mysqli_stmt_execute($stmt);
		$data = mysqli_stmt_get_result($stmt);
		if (mysqli_num_rows($data)) {
			echo '<a href="admin.php">Administration</a>';
		}
		mysqli_close($con);
	}
}
?>
			<div class="blocs">Catalogue</div><br /><br />
			<ul id="menu" class="classe">
				<li>
					<a href="chaise.php">Chaises &rsaquo;</a>
					<ul>
<?php
$req = "SELECT DISTINCT modele,modele FROM `chaise`;";
if ($res = mysqli_query($mysqli, $req))
{
	$row = array();
	while (($row = mysqli_fetch_row($res)) != NULL)
	{
		$name = $row['1'];
		echo "<a href='list_article.php?categorie=chaise&modele=$name'><li>$name</li></a>";
	}
}
else
	echo "Database query failed";
?>
					</ul>
				</li>
			</ul><br />
			<ul class="classe" id="menu">
				<li>
					<a href="table.php">Tables  &rsaquo;</a>
					<ul id="year">
<?php
$req = "SELECT DISTINCT modele,modele FROM `table`;";
if ($res = mysqli_query($mysqli, $req))
{
	$row = array();
	while (($row = mysqli_fetch_row($res)) != NULL)
	{
		$name = $row['1'];
		echo "<a href='list_article.php?categorie=table&modele=$name'><li>$name</li></a>";
	}
}
else
	echo "Database query failed";
?>
					</ul>
				</li>
			</ul><br />
			<ul class="classe" id="menu">
				<li>
					<a href="lampe.php">Lampes &rsaquo;</a>
					<ul id="year">
<?php
$req = "SELECT DISTINCT modele,modele FROM `lampe`;";
if ($res = mysqli_query($mysqli, $req))
{
	$row = array();
	while (($row = mysqli_fetch_row($res)) != NULL)
	{
		$name = $row['1'];
		echo "<a href='list_article.php?categorie=lampe&modele=$name'><li>$name</li></a>";
	}
}
else
	echo "Database query failed";
?>
					</ul>
				</li>
			</ul><br /><br />
		<div class="leftmodule2">
<?php
session_start();
if (!isset($_SESSION['loggued_as'])) {
	echo '<form action="login.php" method="POST" class="log">
		Identifiant: <br /><input type="text" name="login" value="" placeholder="Identifiant" class="sub"><br /    >
		Mot de passe: <br /><input type="password" name ="passwd" value="" placeholder="Mot de passe" class="sub"><br /><br />
		<input type="submit" name="submit" value="Connexion" class="sub">
		</form>';
}
else {
	echo '<p class="ident">Bonjour ' . $_SESSION['loggued_as'] . '</a><br /><p></p>
		<a href="logout.php" class="ident">Deconnexion</a><br />';
}
?>
			<div class="modif">
<?php
if (!$_SESSION['loggued_as'])
{
?>
				 <a href="create.php" class="ident">S'inscrire</a><br /><p>Ou</p>
<?php
}
?>
			<a href="modif.php" class="ident">Modifier son mot de passe</a><br />
			</div>
			<div class="log"><br />
				<a href="panier.php" class="panier">Mon panier</a><p>Total des achats:</p>
			 <?php echo $_SESSION['elmt']; ?> article(s)<br /><input readonly type='text' name='total' value='<?php echo $_SESSION['tot']; ?>&#8364;    ' class='achat'>
			</div>
		</div>
</div>
			<div class="catalog">
<?php
include('config.php');
$mysqli = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass, $mysqli_db);
$i = 0;
if ($_SESSION['basket'] && isset($_SESSION['basket'])) {
	while ($i < count($_SESSION['basket']))
	{
		$array = explode(";" , $_SESSION['basket'][$i]);
		$ID = intval($array['1']);
		$categ_ID = intval($array['0']);
		$qte = $array['2'];
		if ($categ_ID == 1)
			$categ = 'lampe';
		elseif ($categ_ID == 2)
			$categ = 'chaise';
		elseif ($categ_ID == 3)
			$categ = 'table';
		else 
			echo 'ERROR';
		$req = "SELECT * FROM `$categ` WHERE ID=$ID;";
		$data = mysqli_query($mysqli, $req);
		if (mysqli_num_rows($data)) {
			$row = mysqli_fetch_assoc($data);
			echo "<table class='table_panier'><tr><td><img class='image_panier' src=".$row['img']."></td><td>".$row['modele']."</td><td>".$row['couleur']."</td><td> nb:".$qte."</td><td>".$row['price']."&#8364;</td></tr></table>";
		}
		$i++;
	}}
?>
	<a href="delete_basket.php"><input type="button" class="acheter" value="vider"></a>
	<a href="archive.php"><input type="button" class="acheter" value="valider"></a>
			</div>
	</body>
<?php
		mysqli_close($mysqli);
?>
</html>
