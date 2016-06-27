<?php
    session_start();
    include('./config.php');
    if ($_POST['submit'] == "OK" && $_POST['login'] && $_POST['oldpw'] && $_POST['newpw']) {
        $con = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass, $mysqli_db);
        if (mysqli_connect_errno())
        {
            echo "Failed to connect to MySQL: " . mysqli_connect_error();
        }
        else
        {
            $oldpw = hash("whirlpool", $_POST['oldpw']);
            $newpw = hash("whirlpool", $_POST['newpw']);
            $log = $_POST['login'];
            if ($newpw) {
                $stmt = mysqli_prepare($con, "SELECT username, passwd FROM users WHERE username=? AND passwd=?;");
                mysqli_stmt_bind_param($stmt, "ss", $log, $oldpw);
                mysqli_stmt_execute($stmt);
                $data = mysqli_stmt_get_result($stmt);
                if (mysqli_num_rows($data) == 1) {
                    $stmt = mysqli_prepare($con, "UPDATE users SET passwd=? WHERE username=?;");
                    mysqli_stmt_bind_param($stmt, "ss", $newpw, $log);
                    mysqli_stmt_execute($stmt);
                    include('./logout.php');
                }
            }
            else {
            mysqli_close($con);
                echo 'Wrong passwd or login';
            }
            mysqli_close($con);
            if ($name || $newpw) {
                header('Location: index.php');
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
            <input class="sub" type="text" autofocus name="login"/></br>
            Old passwd:
            <input class="sub" type="password" name="oldpw"/></br>
            New passwd:
            <input class="sub" type="password" name="newpw"/></br>
            <input class="sub" type="submit" name="submit" value="OK"/>
        </form>
        <form action="suppr_user_1.php" method="post">
            <input class="sub" type="submit" name="sup" value="SUPPRESSION COMPTE"/>
        </form>
        <a href="index.php">Retour à l'index</a>
    </body>
</html>
