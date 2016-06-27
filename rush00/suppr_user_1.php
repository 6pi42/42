<?php
    session_start();
    include('config.php');
    if ($_POST['sup'] && $_SESSION['loggued_as']) {
        $con = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass, $mysqli_db);
        if (mysqli_connect_errno()) {
            echo "Failed to connect to MySQL: " . mysqli_connect_errno();
        }
        else {
        $log = $_SESSION['loggued_as'];
        $stmt = mysqli_prepare($con, "SELECT username FROM users WHERE username=?;");
        mysqli_stmt_bind_param($stmt, "s", $log);
        mysqli_stmt_execute($stmt);
        $data = mysqli_stmt_get_result($stmt);
        if (mysqli_num_rows($data)) {
            $stmt = mysqli_prepare($con, "DELETE FROM `users` WHERE username=?;");
            mysqli_stmt_bind_param($stmt, "s", $log);
            mysqli_stmt_execute($stmt);
            $data = mysqli_stmt_get_result($stmt);
            header('Location: ./logout.php');
        }
    }}
?>
