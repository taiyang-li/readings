<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/> 
<?php
include_once("database.php");
include_once("permission.php");

$account_no = $_SESSION["account_no"];      // 老师或管理员账号
$course_no = $_GET["course_no"];            // 课程号 

if (is_admin())  // 管理员
    $sql = "delete from course where course_no = $course_no";
else if (is_teacher())  // 教师 
    $sql = "delete from course where course_no=$course_no and status='未审核' and teacher_no=$account_no";
else            // 学生或其他人
{
    $message="您无权删除该课程！<br/>";
    header("Location:index.php?message=$message");
    return;
}

get_connection();
mysql_query($sql);
$affected_rows = mysql_affected_rows(); 

echo $affected_rows;
echo "<br/>";

close_connection();
if ($affected_rows > 0) 
    $message = "课程号为：" . $course_no . "的课程已经成功被删除";
else
    $message = "课程号为：" . $course_no . "的课程删除失败";
header("Location:index.php?message=$message"); 
?>
