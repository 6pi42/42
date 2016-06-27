<?php
session_start();
include('./config.php');
if (!isset($_SESSION['basket']))
{
	$_SESSION['basket'] = array();
}
if ($_POST['submit'] == 'Ajouter')
{
	if (!isset($_SESSION['price']))
		$_SESSION['price'] = 0;
	if (!isset($_SESSION['elmt']))
		$_SESSION['elmt'] = 0;
	$categ = $_POST['categ'];
	if ($categ == 'lampe')
		$categ = 1;
	if ($categ == 'chaise')
		$categ = 2;
	if ($categ == 'table')
		$categ = 3;
	$i = 0;
	$q = 1;
	$_SESSION['tot'] += $_POST['price'];
	$_SESSION['elmt'] += 1;
	while ($i < count($_SESSION['basket']))
	{
		$array = explode(";" , $_SESSION['basket'][$i]);
		if ($array[0] == $categ && $array[1] == $_POST['ID']) {
			$q = intval($array[2]) + 1;
			$_SESSION['basket'][$i] = $categ.";".$_POST['ID'].";".strval($q);
			break ;
		}
		$i++;
	}
	if ($q == 1) {
		$_SESSION['basket'][] = $categ.";".$_POST['ID'].";".strval($q);
	}
	header('Refresh:1; url=article.php?categorie='.$_POST["categ"].'&ID='.$_POST["ID"]);
}
?>
