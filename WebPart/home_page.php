<?php
include 'connect_db.php';
session_start();
$username = $_SESSION["username"];
$sql = "SELECT * FROM ".$username;
$result = mysqli_query($connection,$sql);
/*
var agr_water_lev = google.visualization.arrayToDataTable([
		['Label', 'Value'],
		['Water Level',<?php
		$sql = "SELECT * FROM ".$username." WHERE id = (SELECT MAX(id) FROM ".$username.")";
		$row = mysqli_fetch_array($result);
		echo $row['wate_level'];
		?>]
	]);

	var agr_options = {
					 width: 400, height: 120,
					 redFrom: 90, redTo: 100,
					 yellowFrom:75, yellowTo: 90,
					 minorTicks: 1
				 };
*/
?>

<html>
<head>
	<title>Welcome</title>
	<meta charset="utf-8">
  <meta http-equiv="refresh" content="5" >
	<link rel="stylesheet" type="text/css" href="styles.css">
	<script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
	<script type="text/javascript">
	google.charts.load('current', {'packages':['corechart']});
	google.charts.load('current', {packages: ['gauge']});
	google.charts.setOnLoadCallback(drawChart);
	google.charts.setOnLoadCallback(drawNew);
	function drawChart() {
		var data = google.visualization.arrayToDataTable([
			['Count', 'temperature', 'moisture'],
			<?php
					while($row = mysqli_fetch_array($result)){
							echo "['".$row["id"]."', ".$row["temperature"].", ".$row['moisture']."],";
					}
			?>
		]);

		var options = {
			title: 'Sensor Data',
			curveType: 'function',
			legend: { position: 'bottom' }
		};

		var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));

		chart.draw(data, options);
	}
	function drawNew() {

		var data = google.visualization.arrayToDataTable([
			['Label', 'Value'],
			['Water Level',<?php
			$sql = "SELECT * FROM ".$username." WHERE id = (SELECT MAX(id) FROM ".$username.")";
			$result = mysqli_query($connection,$sql);
			$row = mysqli_fetch_array($result);
			echo $row['wate_level'];
			?>]
		]);

		var options = {
			width: 250, height: 250,
			redFrom: 90, redTo: 100,
			yellowFrom:75, yellowTo: 90,
			minorTicks: 5
		};

		var chart = new google.visualization.Gauge(document.getElementById('chart_div'));

		chart.draw(data, options);
	}

	</script>

</head>
<body>
  <h1>
  	IOT Based Smart Village - MP Mini Project
  </h1>
<?php
	$sql = "SELECT * FROM ".$username." WHERE id = (SELECT MAX(id) FROM ".$username.")";
  $result = mysqli_query($connection,$sql);
  $row = mysqli_fetch_array($result);
	echo "<table id = \"myTable\" style=\"width:100%\">
  <tr>
	<th>
	<h2> Agriculture NODE </h2>
	</th>
	<th><h2> Irrigation NODE </h2></th>
	</tr>";
	  echo "<tr><td><h4>Temperature of Soil: ".$row['temperature']."</h4></td></tr>";
	  echo "<tr><td><h4>Moisture of Soil - A: ".$row['moisture']."</h4><td><h4>Water Level: ".$row['irr_water_level']."</h4></td></tr></td>";
	  //echo "<h4>Humidity of Soil - B: ".$row['humidity']."</h4>";
	  //echo "<h4>pH of Water: ".$row['ph']."</h4>";
	  echo "<tr><td><h4>Water level in Reservoir: ".$row['wate_level']."</h4></td></tr>";
	  if($row['agri_motor'] == 0)
		{
		if($row['irr_motor'] == 0)
			echo "<tr><td><h4>Status of Motor: OFF</h4></td><td><h4>Status of Motor: OFF</h4></td></tr>";
		else
			echo "<tr><td><h4>Status of Motor: OFF</h4></td><td><h4>Status of Motor: ON</h4></td></tr>";
		}
	  else
		{
		if($row['irr_motor'] == 0)
			echo "<tr><td><h4>Status of Motor: ON</h4></td><td><h4>Status of Motor: OFF</h4></td></tr>";
		else
			echo "<tr><td><h4>Status of Motor: ON</h4></td><td><h4>Status of Motor: ON</h4></td></tr>";
		}

	  echo "<tr><td><form action = \"home_page.php\" method=\"POST\">
	  		<input type=\"submit\" name = \"motor_on\" value=\"Motor On\">
	  	  </form></td><td><form action = \"home_page.php\" method=\"POST\">
						<input type=\"submit\" name = \"irr_motor_on\" value=\"Motor on\">
						</form></td></tr>";
	  echo "<tr><td><form action = \"home_page.php\" method=\"POST\">
	  		<input type=\"submit\" name = \"motor_off\" value=\"Motor Off\">
	  	  </form></td><td><form action = \"home_page.php\" method=\"POST\">
						<input type=\"submit\" name = \"irr_motor_off\" value=\"Motor Off\">
						</form></td></tr>";
	echo "</td>";


	echo "</table>";
	if(isset($_POST['motor_on']))
	{
		$sql = "UPDATE ".$username." SET agri_motor = 1";
		$response = mysqli_query($connection,$sql);
	}
	if(isset($_POST['motor_off']))
	{
		$sql = "UPDATE ".$username." SET agri_motor = 0";
		$response = mysqli_query($connection,$sql);
	}
			if(isset($_POST['irr_motor_on']))
			{
				$sql = "UPDATE ".$username." SET irr_motor = 1";
				$response = mysqli_query($connection,$sql);
			}
			if(isset($_POST['irr_motor_off']))
			{
				$sql = "UPDATE ".$username." SET irr_motor = 0";
				$response = mysqli_query($connection,$sql);
			}
 ?>
 <div id="curve_chart" style="width: 500px; height: 300px"></div>
 <div id="chart_div" style="width: 400px; height: 120px;"></div>
</body>
</html>
