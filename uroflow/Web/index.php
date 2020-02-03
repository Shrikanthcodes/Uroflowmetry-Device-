<?php

	include("connect.php"); 	
	
	$link=Connection();

	$result=mysql_query("SELECT * FROM `uro` ORDER BY `timeStamp` DESC",$link);
?>

<html>
   <head>
      <title>Sensor Data</title>
   </head>
<body>
   <h1>Uro sensor readings</h1>

   <table border="1" cellspacing="1" cellpadding="1">
		<tr>
			<td>&nbsp;Timestamp&nbsp;</td>
			<td>&nbsp;Ml&nbsp;</td>

      <?php 
		  if($result!==FALSE){
		     while($row = mysql_fetch_array($result)) {
		        printf("<tr><td> &nbsp;%s </td><td> &nbsp;%s&nbsp; </td></tr>", 
		           $row["timeStamp"], $row["ml"]);
		     }
		     mysql_free_result($result);
		     mysql_close();
		  }
      ?>

   </table>
</body>
</html>
