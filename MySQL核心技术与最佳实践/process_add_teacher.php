<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php
include_once("database.php");        // 包含链接数据库函数
$password = $_POST["password"];      // 获取form 密码
$re_password = $_POST["re_password"];
$teacher_no = $_POST["teacher_no"];     // 教师工号
$teacher_name = $_POST["teacher_name"];  // 教师姓名  
$teacher_contact = $_POST["teacher_contact"];  // 联系方式
$message = "";                              

if ($password == $re_password)  
{
    $insert_sql = "insert into teacher values('$teacher_no', md5('$password'), '$teacher_name', '$teacher_contact')";
    get_connection();
    mysql_query($insert_sql);
    $affected_rows = mysql_affected_rows(); 
	echo $affected_rows;
    close_connection();
    if ($affected_rows > 0)
        $message = "教师添加成功";
    else
        $message = "教师添加失败";
}
else
    $message = "密码与确认密码不一致，注册失败";
header("Location:index.php?message=$message"); // 将页面重定向到首页 并且传递信息

?>

