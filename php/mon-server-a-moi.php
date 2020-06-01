<?php 
include('/opt/lampp/htdocs/example/vendor/autoload.php');

$host = '127.0.0.1';
$port = 8086;
$dbname = 'aTimeSeries';

//directly get the database object
$database = \InfluxDB\Client::fromDSN(sprintf('influxdb://user:pass@%s:%s/%s', $host, $port, $dbname));

//query of the last value
$result = $database->query('select * from valeurs group by * order by desc limit 1');

//get the point
$points = $result->getPoints();

//make the array right
$points = json_encode($points);
$points = json_decode($points);

//take only the seconds of the time
$points[0]->time = substr($points[0]->time, 0,20);

// Set the JSON header
header("Content-type: text/json");

// The x value is the current JavaScript time, which is the Unix time multiplied by 1000 and take the time
$x = strtotime($points[0]->time) * 1000;

// The y value take the value which is a random value
$y = $points[0]->value;

// Create a PHP array and echo it as JSON
$ret = array($x, $y);
echo json_encode($ret);

?>
