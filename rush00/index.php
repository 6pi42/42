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
if (isset($_SESSION['loggued_as']) && $_SESSION['loggued_as'] != 'GUEST') {
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
		Identifiant: <br /><input type="text" name="login" value="" placeholder="Identifiant" class="sub"><br />
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
				<?php echo $_SESSION['elmt']; ?> article(s)<br /><input readonly type='text' name='total' value='<?php echo $_SESSION['tot']; ?>&#8364;' class='achat'>
			</div>
		</div>
</div>
			<div class="catalog">
<?php
$req = "SELECT * FROM `chaise` ORDER BY `ID`";
$req2 = "SELECT * FROM `table` ORDER BY `ID`";
$req3 = "SELECT * FROM `lampe` ORDER BY `ID`";
if ($res = mysqli_query($mysqli, $req))
{
	$row = array();
	while (($row = mysqli_fetch_row($res)) != NULL)
	{
		$img = $row['3'];
		$name = $row['1'];
		$prix = $row['2'];
		$ID = $row['0'];
		echo "<a href='article.php?categorie=chaise&ID=$ID'><div id='article'>"
			."<center><img src='$img' class='image_catalog'></center>"
			."<div id='detail'>$name : $prix&#8364;</div></div></a>";
	}
}
else 
	echo "Database query failed";
if ($res2 = mysqli_query($mysqli, $req2))
{
	$row2 = array();
	while (($row2 = mysqli_fetch_row($res2)) != NULL)
	{
		$img = $row2['3'];
		$name = $row2['1'];
		$prix = $row2['2'];
		$ID = $row2['0'];
		echo "<a href='article.php?categorie=table&ID=$ID'><div id='article'>"
			."<center><img src='$img' class='image_catalog'></center>"
			."<div id='detail'>$name : $prix&#8364;</div></div></a>";
	}
}
else 
	echo "Database query failed";
if ($res3 = mysqli_query($mysqli, $req3))
{
	$row3 = array();
	while (($row3 = mysqli_fetch_row($res3)) != NULL)
	{
		$img = $row3['3'];
		$name = $row3['1'];
		$prix = $row3['2'];
		$ID = $row3['0'];
		echo "<a href='article.php?categorie=lampe&ID=$ID'><div id='article'>"
			."<center><img src='$img' class='image_catalog'></center>"
			."<div id='detail'>$name : $prix&#8364;</div></div></a>";
	}
}
else 
	echo "Database query failed";
?>
			</div>
	</body>
<?php
mysqli_close($mysqli);
?>
</html>
