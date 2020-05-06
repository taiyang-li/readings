<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php
include_once("database.php");    
$class_name = $_POST["class_name"];
$department_name = $_POST["department_name"];
$insert_sql = "insert into classes values(null, '$class_name', '$department_name')";
get_connection();
mysql_query($insert_sql);
$affected_rows = mysql_affected_rows();
close_connection();
if ($affected_rows > 0)
    $message = "班级添加成功";
else
    $message = "班级添加失败";
header("Location:index.php?message=$message");
?>

