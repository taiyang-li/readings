<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php
include_once("permission.php");
include_once("database.php");
if (!is_admin())
{
    $message = "您无权取消已经审核的课程！<br/>";
    header("Location:index.php?message=$message");
    return;
}
else
{
    $course_no = $_GET["course_no"];
    $sql = "update course set status='未审核' where course_no=$course_no and status='已审核'";
    get_connection();
    mysql_query($sql);
    $affected_rows = mysql_affected_rows();
    close_connection();
    if ($affected_rows > 0)
        $message = "课程号为：" . $course_no . "的课程已经成功取消审核！";
    else
        $message = "课程号为：" . $course_no . "的课程取消审核失败！";
    header("Location:index.php?message=$message"); 
}
?>
