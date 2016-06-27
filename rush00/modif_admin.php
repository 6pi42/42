<?php
    session_start();
    include('verif_admin.php');
    include('./config.php');
    if ($_POST['submit'] == "OK" && $_POST['login'] && ($_POST['passwd'] || $_POST['email'] || $_POST['adresse'])) {
        $con = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass, $mysqli_db);
        if (mysqli_connect_errno())
        {
            echo "Failed to connect to MySQL: " . mysqli_connect_error();
        }
        else
        {
            $pw = hash("whirlpool", $_POST['passwd']);
            $log = $_POST['login'];
            $mail = $_POST['email'];
            $adresse = $_POST['adresse'];
            $stmt = mysqli_prepare($con, "SELECT username FROM users WHERE username=?;");
            mysqli_stmt_bind_param($stmt, "ss", $log);
            mysqli_stmt_execute($stmt);
            $data = mysqli_stmt_get_result($stmt);
            if (mysqli_num_rows($data) == 1) {
                if ($_POST['passwd']) {
                    $stmt = mysqli_prepare($con, "UPDATE users SET passwd=? WHERE username=?;");
                    mysqli_stmt_bind_param($stmt, "ss", $pw, $log);
                    mysqli_stmt_execute($stmt);
                }
                if ($_POST['email']) {
                    $stmt = mysqli_prepare($con, "UPDATE users SET email=? WHERE username=?;");
                    mysqli_stmt_bind_param($stmt, "ss", $mail, $log);
                    mysqli_stmt_execute($stmt);
                }
                if ($_POST['adresse']) {
                    $stmt = mysqli_prepare($con, "UPDATE users SET adresse=? WHERE username=?;");
                    mysqli_stmt_bind_param($stmt, "ss", $adresse, $log);
                    mysqli_stmt_execute($stmt);
                }
                mysqli_close($con);
                header('Location: admin.php');
            }
            else {
                echo 'Wrong login';
                mysqli_close($con);
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
        <h1>Modifier mot de passe</h1>
        <form action="modif.php" method="post">
            Username:
            <input type="text" autofocus name="login"/></br>
            New passwd:
            <input type="password" name="passwd"/></br>
            New email:
            <input type="email" name="email"/></br>
            New adress:
            <input type="text" name="adresse"/></br>
            <input type="submit" name="submit" value="OK"/>
        </form>
        <a href="admin.php">Retour à la page d'administration</a>
    </body>
</html>
