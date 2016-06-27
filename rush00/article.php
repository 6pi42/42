<?php
session_start();
include'config.php';
$mysqli = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass, $mysqli_db);
if (!$mysqli)
{
	echo "Database connection failed";
}
if ($_GET['categorie'] == "chaise")
	$categ = "chaise";
if ($_GET['categorie'] == "table")
	$categ = "table";
if ($_GET['categorie'] == "lampe")
	$categ = "lampe";
if ($_GET['ID'] != NULL)
	$ID = $_GET['ID'];
else if ($_GET['modele'] != NULL)
	$modele = $_GET['modele'];
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
			<div class="article_unique">
<?php
if ($ID != NULL)
	$req = "SELECT * FROM `$categ` WHERE ID=$ID;";
if ($res = mysqli_query($mysqli, $req))
{
	$row = array();
	while (($row = mysqli_fetch_row($res)) != NULL)
	{
		$name = $row['1'];
		$prix = $row['2'];
		$img = $row['3'];
		$couleur = $row['4'];
		$stock = $row['5'];
?>
	<form method="POST" action="ajout_panier.php">
	<table align="center">
		<tr>
			<td>
				<img src='<?php echo $img; ?>' class='image_article'>
			</td>
		</tr>
		<tr>
			<td>
				<div class='detail_article'>
					<?php echo "$name : $prix"; ?>&#8364;<br /><br />
<?php echo "couleur : $couleur<br />";
if ($stock > 0)	
	echo "Stock : $stock unit&eacute;e(s) restante(s)";
else
	echo "Produit en rupture de stock";
?>
					<br /><br />
					<input type='submit' name="submit" class='acheter' value='Ajouter'>
				</div>
			</td>
		<tr>
	</table>
	<input type="hidden" name="ID" value="<?php echo $_GET['ID'] ?>">
	<input type="hidden" name="categ" value="<?php echo $_GET['categorie'] ?>">
	<input type="hidden" name="modele" value="<?php echo $name ?>">
	<input type="hidden" name="price" value="<?php echo $prix ?>">
	<input type="hidden" name="img" value="<?php echo $img ?>">
	<input type="hidden" name="couleur" value="<?php echo $couleur ?>">
</form>
<?php
	}
}
?>
			</div>
	</body>
<?php
mysqli_close($mysqli);
?>
</html>
