<?php
session_start();
include('./verif_admin.php');
include('./config.php');
if ($_POST['submit'] == 'OK' && $_POST['id'] &&
$_POST['modele'] && $_POST['img'] && $_POST['couleur'] && $_POST['stock']
&& $_POST['id_categ'] && $_POST['price']) {
    $con = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass, $mysqli_db);
    if (mysqli_connect_errno()) {
        echo "Failed to connect to MySQL: " . mysqli_connect_error();
    }
    else {
        $couleur = $_POST["couleur"];
        $id = intval($_POST['id']);
        $modele = $_POST['modele'];
        $img = $_POST['img'];
        $stock = intval($_POST['stock']);
        $id_c = intval($_POST['id_categ']);
        $price = intval($_POST['price']);
        if ($id_c == 1) {
            $table = "lampe";
        }
        elseif ($id_c == 2) {
            $table = "chaise";
        }
        elseif ($id_c == 3) {
            $table = "table";
        }
        else {
            header('Location: ./admin.php');
        }
        $req = "SELECT ID FROM ".$table." WHERE ID=?;";
        $stmt = mysqli_prepare($con, $req);
        mysqli_stmt_bind_param($stmt, "i", $id);
        mysqli_stmt_execute($stmt);
        $data = mysqli_stmt_get_result($stmt);
        if ($data && mysqli_num_rows($data) == 0) {
            $stmt = mysqli_prepare($con,"INSERT INTO ".$table." (`ID`, `modele`, `price`, `img`, `couleur`, `stock`, `id_categ`)  VALUES (?, ?, ?, ?, ?, ?, ?);");
            mysqli_stmt_bind_param($stmt, "isissii", $id, $modele, $price, $img, $couleur, $stock, $id_c);
            mysqli_stmt_execute($stmt);
            $data = mysqli_stmt_get_result($stmt);
            mysqli_close($con);
        }
        else {
            echo 'error';
        }
    }
}
?>
<html>
    <head>
        <meta charset="utf-8">
        <link rel="stylesheet" href="style.css">
        <title>Toto-Meubles</title>
    </head>
    <body>
        <h1>Ajout d'un meuble</h1>
        <form action="add_meuble.php" method="post">
            <input class="sub" type="text" placeholder="ID" name="id" autofocus/></br>
            <input class="sub" type="text" placeholder="Modele" name="modele"/></br>
            <input class="sub" type="text" placeholder="Prix" name="price"/></br>
            <input class="sub" type="url" placeholder="Url image" name="img"/></br>
            <input class="sub" type="text" placeholder="Couleur" name="couleur"/></br>
            <input class="sub" type="text" placeholder="Stock" name="stock"/></br>
            <input class="sub" type="text" placeholder="id_categorie" name="id_categ"/></br>
            <input class="sub" type="submit" name="submit" value="OK"/>
        </form>
        <a href="admin.php">Retour à la page d'administration</a>
    </body>
</html>
