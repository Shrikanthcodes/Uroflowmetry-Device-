<?php
   	include("connect.php");
   	
   	$link=Connection();

	$temp1=$_POST["ml"];

	$query = "INSERT INTO `uro` (`ml`) 
		VALUES ('".$temp1."')"; 
   	
   	mysql_query($query,$link);
	mysql_close($link);

   	header("Location: index.php");
?>
