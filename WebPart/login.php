<html>
<head>
	<title>login</title>
	<meta charset="utf-8">
	<link rel="stylesheet" type="text/css" href="styles.css">
</head>
<body>

<?php
include 'connect_db.php';
session_start();
if(isset($_POST['login']))
{
$username = $_POST['username'];
$password = $_POST['password'];
  $_SESSION["username"] = $username;
  $_SESSION["password"] = $password;
  $sql = "SELECT * FROM user_data WHERE username='$username' and pwd = '$password'";
  $result = mysqli_query($connection,$sql);
  $row = mysqli_fetch_array($result);
  $count = mysqli_num_rows($result);
  echo $row;
  if($count == 1)
  {
    header("location: home_page.php");
  }
  else {
    echo "<h2> User doesn't exist. Please Register!</h2>";
    echo "<form action = \"user_form.php\" method=\"POST\">
  		<input type=\"submit\" name = \"register\" value=\"register\">
    </form>";
}
}
 ?>
 </body>
 </html>
