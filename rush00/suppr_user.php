<?php
    session_start();
    include('verif_admin.php');
?>
<html>
	<head>
		<meta charset="utf-8">
		<link rel="stylesheet" href="style.css">
		<title>Toto-Meubles</title>
	</head>
	<body>
		<?php
			include('config.php');
			$con = mysqli_connect($mysqli_host, $mysqli_user, $mysqli_pass, $mysqli_db);
			if (mysqli_connect_errno()) {
				echo "Failed to connect to MySQL: " . mysqli_connect_errno();
			}
			else {
				$data = mysqli_query($con, "SELECT username FROM users;");
				$i = mysqli_num_rows($data);
				$j = 0;
				echo '<h2 style="color:white;">Users</h2>';
				echo '<ul>';
				while ($row = mysqli_fetch_assoc($data)) {
					echo '<li style="color:white;">' . $row['username'] . '</li>';
				}
				echo '</ul>';
			}
			?>
		</br>
		<form action="suppr.php" method="post">
			<input class="sub" type="text" placeholder="Login" name="login"/></br>
			<input class="sub" type="submit" name="submit" value="Confirmer"/>
		</form>
		<a href="admin.php">Retour à l'Administration</a>
	</body>
</html>
