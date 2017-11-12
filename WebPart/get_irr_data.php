<?php
include 'connect_db.php';
if(isset($_GET['username']) && isset($_GET['data']))
{
  $username = $_GET['username'];
  $data = $_GET['data'];

  $water_level = $data;

  $sql = "SELECT * FROM ".$username." WHERE id = (SELECT MAX(id) FROM ".$username.")";

  $result = mysqli_query($connection,$sql);
  $row = mysqli_fetch_array($result);
  $irr_motor = $row['irr_motor'];

  $sql = "INSERT INTO $username (irr_water_level,irr_motor) VALUES('$water_level','$irr_motor')";
  $result = mysqli_query($connection,$sql);

  echo $irr_motor;
}
//http://localhost/MiniProject/get_irr_data.php/?username=saikamalkola&data=100_10_5_2_10
 ?>
