<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php
include_once("database.php");
$account_no = $_POST["account_no"];
$password = $_POST["password"];     # 新密码 
$role = $_POST["role"];
get_connection();
if ($role == "student")
    $sql = "update student set password=md5('$password') where student_no='$account_no'";
else if ($role == "teacher")
    $sql = "update teacher set password=md5('$password') where teacher_no='$account_no'";
$result_set = mysql_query($sql); 
$affected_rows = mysql_affected_rows();
echo $affected_rows; 
close_connection();
if ($affected_rows > 0)
    $message = "账号$account_no" . "的密码修改成功! <br/>";
else
    $message = "账号$account_no" . "的密码修改失败! <br/>";
header("Location:index.php?message=$message");
?>
