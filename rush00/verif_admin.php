<?php
session_start();
include('config.php');
$con = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass, $mysqli_db);
if (mysqli_connect_errno()) {
	echo "Failed to connect to MySQL: " . mysqli_connect_error();
}
else {
	$stmt = mysqli_prepare($con,"SELECT classe, username FROM `users` WHERE classe='3' AND username=?;");
	mysqli_stmt_bind_param($stmt, "s", $_SESSION['loggued_as']);
	mysqli_stmt_execute($stmt);
	$data = mysqli_stmt_get_result($stmt);
	if (mysqli_num_rows($data)) {
		mysqli_close($con);
	}
	else {
		mysqli_close($con);
		header('Location: ./index.php');
	}
}
?>
