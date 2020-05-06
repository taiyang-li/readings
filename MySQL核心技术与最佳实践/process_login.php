<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php
// 
session_start();  # 开启一个会话
include_once("database.php");
$account_no = $_POST["account_no"];       # 账号
$password = $_POST["password"];           # 密码 
$role = $_POST["role"];                   # 教师 学生 或管理员 


get_connection();
if ($role == "student")
    $sql = "select * from student where student_no = '$account_no' and password=md5('$password')";
else if ($role == "teacher")
{
	echo md5($password);
	echo "<br/>";
	echo $account_no;
    $sql = "select * from teacher where teacher_no = '$account_no' and password = md5('$password')";
}
else if($role == "admin")
{	
	/* 
	echo md5($password); 
	echo "<br/>";
	echo "$account_no";
	*/ 
    $sql = "select * from admin where admin_no = '$account_no' and password = md5('$password')";
}


# 提交select语句 
$result_set = mysql_query($sql);
$rows=  mysql_num_rows($result_set);
if ($rows == 0)
    header("Location:index.php?message=账号密码有误！");
	#;
else
{
    # 记录登陆账户信息 方便下一步对话   
	// 其实此时已经记录了用户的登陆信息 
    $account = mysql_fetch_array($result_set);
    $_SESSION["role"] = $role;
    $_SESSION["account_no"] = $account[0];   
    $_SESSION["account_name"] = $account[2];
    header("Location:index.php?message=登陆成功！");
    return; 
}
close_connection();  # 关闭数据库服务器链接 


?>
