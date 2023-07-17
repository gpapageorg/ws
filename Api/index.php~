<?php
$got = $_GET['query'];

$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "ws";

$temp = array();


// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
  echo "Error";
}

$sql = "SELECT * FROM data ORDER BY num DESC LIMIT 2";
$result = $conn->query($sql);

if ($result->num_rows > 0) {

while($row = $result->fetch_assoc()) {
	$data = new stdClass();
	$data -> id = $row["id"];
	$data -> temp = $row["temp"];
	$data -> humidity = $row["humidity"];
	$data -> pressure = $row["pressure"];
	$data -> alt = $row["alt"];
	$data -> timestamp = $row["timestamp"];

	if($data -> id >= 0)
		$temp[$data -> id] = $data;

	#array_push($temp,$data);
 }
} else {
  //echo "0 results";
}




if (!strcmp($got, "all"))
{
	header("Content-Type: application/json");
	$myJSON = json_encode($temp);
	echo $myJSON;
}
else
	echo "You filthy animal";

$conn->close();
?>
