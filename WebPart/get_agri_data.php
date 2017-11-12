<?php
include 'connect_db.php';
if(isset($_GET['username']) && isset($_GET['data']))
{
  $username = $_GET['username'];
  $data = $_GET['data'];
  $data = explode('_', $data);
  $temperature = $data[0];
  $moisture = $data[1];
  $humidity = $data[2];
  $water_level = $data[3];
  $ph = $data[4];

  $sql = "SELECT * FROM ".$username." WHERE id = (SELECT MAX(id) FROM ".$username.")";
  $result = mysqli_query($connection,$sql);
  $row = mysqli_fetch_array($result);
  $agri_motor = $row['agri_motor'];

  $sql = "INSERT INTO $username (temperature,moisture,humidity,wate_level,ph,agri_motor) VALUES('$temperature','$moisture','$humidity','$water_level','$ph','$agri_motor')";
  $result = mysqli_query($connection,$sql);

  echo $agri_motor;
}
//http://localhost/MiniProject/get_agri_data.php/?username=saikamalkola&data=100_10_5_2_10
 ?>
