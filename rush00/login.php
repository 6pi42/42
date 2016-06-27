<?php
session_start();
include('./config.php');
if ($_POST['submit'] == "Connexion" && $_POST['login'] && $_POST['passwd']) {
        $con = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass, $mysqli_db);
        if (mysqli_connect_errno()) {
                echo "Failed to connect to MySQL: " . mysqli_connect_error();
        }
        else
        {
                $pw = hash("whirlpool", $_POST['passwd']);
                $log = $_POST['login'];
                $stmt = mysqli_prepare($con, "SELECT * FROM users WHERE username=? AND passwd=?;");
                mysqli_stmt_bind_param($stmt, "ss", $log, $pw);
                mysqli_stmt_execute($stmt);
                $data = mysqli_stmt_get_result($stmt);
                if (mysqli_num_rows($data) == 1) {
                        $_SESSION['loggued_as'] = $log;
						$req = "SELECT * FROM `panier` WHERE username='$log';";
						$data = mysqli_query($con, $req);
						if (mysqli_num_rows($data)) {
							$row = mysqli_fetch_assoc($data);
							$_SESSION['basket'] = unserialize($row['data']);
						}
                        mysqli_close($con);
                        header("Refresh: 1; url=index.php");
                }
                else {
                        echo 'Wrong login or passwd';
                        mysqli_close($con);
                }
        }
}
?>
