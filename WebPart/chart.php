<?php
include 'connect_db.php';
$sql = "SELECT * FROM saikamalkola";
$result = mysqli_query($connection,$sql);
?>

<html>
  <head>
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
          ['Memory', 80],
          ['CPU', 55],
          ['Network', 68]
        ]);

        var options = {
          width: 400, height: 120,
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
    <div id="curve_chart" style="width: 900px; height: 500px"></div>

    <div id="chart_div" style="width: 400px; height: 120px;"></div>
  </body>
</html>
