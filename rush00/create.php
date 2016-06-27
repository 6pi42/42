<?php
    session_start();
    include('./config.php');
    if ($_SESSION['loggued_as'] ==  "" || !isset($_SESSION['loggued_as'])) {
        if ($_POST['submit'] == "OK" && $_POST['login'] && $_POST['passwd'] && $_POST['name'] && $_POST['email'] && $_POST['adresse']) {
            $con = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass, $mysqli_db);
            if (mysqli_connect_errno()) {
                echo "Failed to connect to MySQL: " . mysqli_connect_errno();
            }
            else {
                $pw = hash("whirlpool", $_POST['passwd']);
                $log = $_POST['login'];
                $name = $_POST['name'];
                $stmt = mysqli_prepare($con, "SELECT username, name, email FROM users WHERE username=? OR name=? OR email=?;");
                mysqli_stmt_bind_param($stmt, "sss", $log, $name, $_POST['email']);
                mysqli_stmt_execute($stmt);
                $data = mysqli_stmt_get_result($stmt);
                if (mysqli_num_rows($data) == 0) {
                    $stmt = mysqli_prepare($con, "INSERT INTO `users` (`username`, `passwd`, `name`, `classe`, `email`, `adresse`) VALUES(?, ?, ?, '0',?, ?);");
                    mysqli_stmt_bind_param($stmt, "sssss", $log, $pw, $name, $_POST['email'], $_POST['adresse']);
                    mysqli_stmt_execute($stmt);
                    $data = mysqli_stmt_get_result($stmt);
                    mysqli_close($con);
                    header('Location: index.php');
                }
                else {
                    mysqli_close($con);
                    echo 'Wrong login';
                }
            }
        }
    }
    else {
        header('Location: index.php');
    }
?>
<html>
    <head>
        <meta charset="utf-8">
        <link rel="stylesheet" href="style.css">
        <title>Toto-Meubles</title>
    </head>
    <body>
        <h1>Création de compte</h1>
        <form action="create.php" method="post">
            <input class="sub" type="text" placeholder="Name" name="name"/></br>
            <input class="sub" type="text" placeholder="Username" autofocus name="login"/></br>
            <input class="sub" type="password" placeholder="Mot de passe" name="passwd"/></br>
            <input class="sub" type="email" placeholder="Email" name="email"/></br>
            <input class="sub" type="text" placeholder="Adresse" name="adresse"/></br>
            <input class="sub" type="submit" name="submit" value="OK"/>
        </form>
        <a href="index.php">Retour à l'index</a>
    </body>
</html>
