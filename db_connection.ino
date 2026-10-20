<?php
function OpenCon()
{
	$con= mysqli_connect("host", "username",
                     "DatabasePassword", "databasename", "port");
	return $con;
 }
 
function CloseCon($con)
{
	$con -> close();
}
   
?>