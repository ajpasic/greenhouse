<?php
  // connect to the test database
  require_once 'login.php';
  $conn = new mysqli($hn, $un, $pw, $db);
  if ($conn->connect_error) die($conn->connect_error);

  // query the database for all entries
  $query = "SELECT * FROM users";
  $result = $conn->query($query);
  if (!$result) die($conn->connect_error);

  // from result, print all entries
  $rows = $result->num_rows;
  for ($j = 0; $j < $rows; ++$j)
  {
    $result->data_seek($j);
    $row = $result->fetch_array(MYSQLI_ASSOC);
    echo 'First name: ' . $row['firstname'] . '<br>';
    echo 'Last name: '  . $row['lastname']  . '<br>';
    echo 'Plant: '   	. $row['plant']	    . '<br>';
  }

  $result->close(); // release result
  $conn->close(); // terminate connection
?>
