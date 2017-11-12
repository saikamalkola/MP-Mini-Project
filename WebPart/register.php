<!DOCTYPE html>
<html>
<head>
	<title>Registration Successfull</title>
	<meta charset="utf-8">
	<link rel="stylesheet" type="text/css" href="styles.css">
</head>
<body>

<?php
include 'connect_db.php';

if(isset($_POST['register']))
{
  $username = $_POST['username'];
  $firstname = $_POST['firstname'];
  $lastname = $_POST['lastname'];
  $email = $_POST['email_id'];
  $aadhaar = $_POST['aadhaar'];
  $password = $_POST['password'];
  $sql = "INSERT INTO user_data (username,firstname,lastname,email,aadhaar,pwd) VALUES('$username','$firstname','$lastname','$email','$aadhaar','$password')";
  $result = mysqli_query($connection,$sql);
  $sql = "CREATE TABLE ".$username.'(
  id INT(10) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  temperature INT(10) UNSIGNED NOT NULL,
  moisture int(10) UNSIGNED NOT NULL,
  humidity int(10) UNSIGNED NOT NULL,
  ph int(10) UNSIGNED NOT NULL,
  wate_level int(10) UNSIGNED NOT NULL,
  agri_motor int(10) UNSIGNED NOT NULL,
  irr_motor int(10) UNSIGNED NOT NULL,
	irr_water_level int(10) UNSIGNED NOT NULL,
  appliances int(10) UNSIGNED NOT NULL,
  KWH_1 int(10) UNSIGNED NOT NULL,
  KWH_2 int(10) UNSIGNED NOT NULL,
  KWH_3 int(10) UNSIGNED NOT NULL,
  KWH_4 int(10) UNSIGNED NOT NULL,
  KWH_5 int(10) UNSIGNED NOT NULL,
  KWH_6 int(10) UNSIGNED NOT NULL,
  KWH_7 int(10) UNSIGNED NOT NULL,
  KWH_8 int(10) UNSIGNED NOT NULL,
  time_stamp TIMESTAMP
  )';
  $response = mysqli_query($connection,$sql);
  if ($response === TRUE) {
      echo "<h1> Registration successful </h1><br>";
  } else {
      echo "Error creating table: " . $connection->error;
  }
}
?>
  <form action = "login_form.php" method="POST">
		<input type="submit" name = "" value="login">
  </form>
</body>
</html>
