<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php
// 此处sesison_start应当这么理解
// index.php作为左右php文件的入口
// 可以用于  注册 教师登陆 学生登录 管理员登陆 
// 以上四种情况，都必须调用session_start();
// 
session_start();
include_once("permission.php"); 
if (is_teacher()) # 申报课程 浏览自己申报的课程 浏览通过审核的课程  
{
?>
    <a href="index.php?url=course_list.php">浏览通过审核的课程</a>
    <a href="index.php?url=teacher_course_list.php">浏览自己申报的课程</a> 
    <a href="index.php?url=add_course.php">申报课程</a>
    <a href="index.php?url=logout.php">注销</a>
<?php
    echo "欢迎您, 教师：" . $_SESSION["account_name"] . "<br/>"; // 读取了$_SESSION的值 
}
elseif (is_student())
{
?>
    <a href="index.php?url=course_list.php">浏览通过审核的课程</a>
    <a href="index.php?url=student_course_list.php">查看自己选修的课程</a>
    <a href="index.php?url=logout.php">注销</a>
<?php
    echo "欢迎您，学生：" . $_SESSION["account_name"] . "<br/>";  // 读取$_SESSION的值
}
elseif (is_admin())
{
?>
    <a href="index.php?url=course_list.php">浏览所有课程</a>
    <a href="index.php?url=add_class.php">添加班级</a>
    <a href="index.php?url=less_course_list.php">浏览选课人数少于30人的课程</a>
    <a href="index.php?url=reset_password.php">重置教师或者学生的密码</a>
    <a href="index.php?url=logout.php">注销</a>  
<?php
    echo "欢迎您，" . $_SESSION["account_name"] . "<br/>";      // 读取$_SESSION的值   
}
else             # 游客
{
?>
    <a href="index.php?url=course_list.php">浏览课程</a>
    <a href="index.php?url=add_student.php">学生注册</a>
    <a href="index.php?url=add_teacher.php">教师注册</a>
    <a href="index.php?url=login.php">登陆</a>
<?php
    echo "您的身份是游客" . "<br/>";
}
?>

<hr>
<?php
if (isset($_GET["message"]))  # 显示处理的状态
    echo "<font color='red'>" . $_GET["message"] . "</font>";

if (isset($_GET["url"]))   # 显示业务数据
    include_once($_GET["url"]);
else
    include_once("course_list.php");    // 默认显示课程列表页面
?>





