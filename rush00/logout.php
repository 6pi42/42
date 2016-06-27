<?php
    session_start();
    unset($_SESSION['loggued_as']);
    unset($_SESSION['basket']);
    $_SESSION['tot'] = 0;
    $_SESSION['elmt'] = 0;
    header('Location: ./index.php');
    exit();
?>
