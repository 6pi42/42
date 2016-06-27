<?php
include('./config.php');
$mysqli = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass);
mysqli_query($mysqli, "CREATE DATABASE $mysqli_db");
mysqli_close($mysqli);

$mysqli = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass, $mysqli_db);
$req = "CREATE TABLE IF NOT EXISTS `users` (`username` varchar(255) NOT NULL,`passwd` varchar(255) NOT NULL,`name` varchar(255) NOT NULL,`classe` int(11) NOT NULL,`email` varchar(255) NOT NULL, `adresse` varchar(255) NOT NULL, UNIQUE KEY `username` (`username`)) ENGINE=InnoDB DEFAULT CHARSET=utf8;";
mysqli_query($mysqli, $req);
$req = "INSERT INTO `users` (`username`, `passwd`, `name`, `classe`, `email`, `adresse`) VALUES('Quentin', 'qdiaz', 'Quentin Diaz', '3', 'w@w.w', 'ww'),('admin', '".hash("whirlpool", 'admin')."', 'admin', '3', 'a@a.a', 'aa'), ('client2', 'client2', 'Client2', '0', 'i@i.i', 'ii');";
mysqli_query($mysqli, $req);
$req = " CREATE TABLE IF NOT EXISTS `categorie` (`ID` int(11) NOT NULL AUTO_INCREMENT,`name` text NOT NULL,PRIMARY KEY (`ID`)) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;";
mysqli_query($mysqli, $req);
$req = "INSERT INTO `categorie` (`ID`, `name`) VALUES"
	."(1, 'lampe'),"
	."(2, 'chaise'),"
	."(3, 'table');";
mysqli_query($mysqli, $req);
$req = " CREATE TABLE IF NOT EXISTS `chaise` (`ID` int(11) NOT NULL AUTO_INCREMENT,`modele` text NOT NULL,`price` int(11) NOT NULL,`img` varchar(500) NOT NULL,`couleur` text NOT NULL,`stock` int(11) NOT NULL,`id_categ` int,PRIMARY KEY (`ID`), FOREIGN KEY (`id_categ`) REFERENCES `categorie`(`ID`)) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;";
mysqli_query($mysqli, $req);
$req = "INSERT INTO `chaise` (`ID`, `modele`, `price`, `img`, `couleur`, `stock`, `id_categ`) VALUES"
	."(1, 'BORG', 40, 'http://www.ikea.com/fr/fr/images/products/borje-chaise-blanc__0121732_PE278342_S4.JPG', 'marron', 200, 2),"
	."(2, 'BORG', 40, 'http://www.ikea.com/fr/fr/images/products/borje-chaise-blanc__73963_PE190725_S4.JPG', 'noir', 200, 2),"
	."(3, 'INGOLF', 55, 'http://www.ikea.com/fr/fr/images/products/ingolf-chaise-noir__74017_PE190756_S4.JPG', 'noir', 200, 2),"
	."(4, 'INGOLF', 55, 'http://www.ikea.com/fr/fr/images/products/ingolf-chaise__0238365_PE377893_S4.JPG', 'marron', 200, 2),"
	."(5, 'JANINGE', 40, 'http://www.ikea.com/fr/fr/images/products/janinge-chaise-blanc__0325072_PE517373_S4.JPG', 'blanc', 200, 2),"
	."(6, 'JANINGE', 40, 'http://www.ikea.com/fr/fr/images/products/janinge-chaise-jaune__0325073_PE517376_S4.JPG', 'jaune', 200, 2),"
	."(7, 'VILMAR', 30, 'http://www.ikea.com/fr/fr/images/products/vilmar-chaise-rouge__0125495_PE283075_S4.JPG', 'rouge', 100, 2),"
	."(8, 'VILMAR', 30, 'http://www.ikea.com/fr/fr/images/products/vilmar-chaise-blanc__0214682_PE370791_S4.JPG', 'blanc', 100, 2),"
	."(9, 'VILMAR', 30, 'http://www.ikea.com/fr/fr/images/products/vilmar-chaise-noir__0125493_PE283073_S4.JPG', 'noir', 100, 2);";
mysqli_query($mysqli, $req);
$req = " CREATE TABLE IF NOT EXISTS `table` (`ID` int(11) NOT NULL AUTO_INCREMENT,`modele` text NOT NULL,`price` int(11) NOT NULL,`img` varchar(500) NOT NULL,`couleur` text NOT NULL, `stock` int(11) NOT NULL,`id_categ` int,PRIMARY KEY (`ID`), FOREIGN KEY (`id_categ`) REFERENCES `categorie`(`ID`)) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;";
mysqli_query($mysqli, $req);
$req = "INSERT INTO `table` (`ID`, `modele`, `price`, `img`, `couleur`, `stock`, `id_categ`) VALUES"
	."(1, 'BJURSTA', 160, 'http://www.ikea.com/fr/fr/images/products/bjursta-table-extensible-noir__67535_PE181365_S4.JPG', 'noir', 50, 3),"
	."(2, 'BJURSTA', 160, 'http://www.ikea.com/fr/fr/images/products/bjursta-table-extensible-brun__0106118_PE253937_S4.JPG', 'marron', 50, 3),"
	."(3, 'BJURSTA', 160, 'http://www.ikea.com/fr/fr/images/products/bjursta-table-extensible__73896_PE190678_S4.JPG', 'blanc', 50, 3),"
	."(4, 'GLIVARP', 180, 'http://www.ikea.com/fr/fr/images/products/glivarp-table-extensible-blanc__0180815_PE333339_S4.JPG', 'verre', 30, 3),"
	."(5, 'INGATORP', 290, 'http://www.ikea.com/fr/fr/images/products/ingatorp-table-extensible-noir__0251847_PE390706_S4.JPG', 'noir', 40, 3),"
	."(6, 'INGATORP', 290, 'http://www.ikea.com/fr/fr/images/products/ingatorp-table-extensible-blanc__0146740_PE305745_S4.JPG', 'blanc', 40, 3),"
	."(7, 'STORNAS', 360, 'http://www.ikea.com/fr/fr/images/products/stornas-table-extensible-noir__0106132_PE254165_S4.JPG', 'noir', 20, 3),"
	."(8, 'STORNAS', 360, 'http://www.ikea.com/fr/fr/images/products/stornas-table-extensible-noir__0106132_PE254165_S4.JPG', 'marron', 20, 3);";
mysqli_query($mysqli, $req);
$req = " CREATE TABLE IF NOT EXISTS `lampe` (`ID` int(11) NOT NULL AUTO_INCREMENT, `modele` text NOT NULL, `price` int(11) NOT NULL,`img` varchar(500) NOT NULL,`couleur` text NOT NULL, `stock` int(11) NOT NULL,`id_categ` int,PRIMARY KEY (`ID`), FOREIGN KEY (`id_categ`) REFERENCES `categorie`(`ID`)) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;";
mysqli_query($mysqli, $req);
$req = "INSERT INTO `lampe` (`ID`, `modele`, `price`, `img`, `couleur`, `stock`, `id_categ`) VALUES"
	."(1, 'ARSTID', 50, 'http://www.ikea.com/fr/fr/images/products/arstid-lampadaire-blanc__0390610_PE566328_S4.JPG', 'or', 30, 1),"
	."(2, 'ARSTID', 50, 'http://www.ikea.com/fr/fr/images/products/arstid-lampadaire-blanc__0418890_PE575909_S4.JPG', 'argent', 30, 1),"
	."(3, 'KLABB', 100, 'http://www.ikea.com/fr/fr/images/products/klabb-lampadaire-blanc__0281602_PE419952_S4.JPG', 'blanc', 30, 1),"
	."(4, 'KLABB', 100, 'http://www.ikea.com/fr/fr/images/products/klabb-lampadaire-brun__0281599_PE419953_S4.JPG', 'marron', 30, 1),"
	."(5, 'HEKTAR', 70, 'http://www.ikea.com/fr/fr/images/products/hektar-lampadaire-gris__0149974_PE308131_S4.JPG', 'noir', 30, 1),"
	."(6, 'HEKTAR', 70, 'http://www.ikea.com/fr/fr/images/products/hektar-lampadaire-jaune__0301867_PE426878_S4.JPG', 'bronze', 30, 1),"
	."(7, 'NOT', 12, 'http://www.ikea.com/fr/fr/images/products/not-lampadaire-liseuse-blanc__0255571_PE399686_S4.JPG', 'noir', 30, 1),"
	."(8, 'NOT', 12, 'http://www.ikea.com/fr/fr/images/products/not-lampadaire-liseuse-blanc__0151521_PE309574_S4.JPG', 'blanc', 30, 1);";
mysqli_query($mysqli, $req);
$req = " CREATE TABLE IF NOT EXISTS `panier` (`ID` int(11) NOT NULL AUTO_INCREMENT,`username` varchar(255), `data` varchar(500),PRIMARY KEY (`ID`), FOREIGN KEY (`username`) REFERENCES `users`(`username`)) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;";
mysqli_query($mysqli, $req);

echo "Install [OK]";

mysqli_close($mysqli);
?>
