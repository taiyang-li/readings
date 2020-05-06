<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php
# 取消选修课程  老师可以取消某个学生的选课 学生也可以自己的选课
include_once("permission.php");
include_once("database.php");

if (is_student() || is_teacher())
{
    get_connection();
    $course_no = $_GET["course_no"];
    # 判断是老师还是学生
    if (isset($_GET["student_no"]))  # 老师操作
    {   
        $student_no = $_GET["student_no"];
        $teacher_no = $_SESSION["account_no"];
        $select_sql = "select course_no from course where course_no=$course_no and teacher_no=$teacher_no";
        $result_set = mysql_query($select_sql);
        if (mysql_num_rows($result_set) == 0)
        {
            $message = "您不是任课教师！";
            header("Location:index.php?message=$message");
            return;
        }
    } 
    else # 学生操作 
    {
        $student_no = $_SESSION["account_no"];
    }

    # 删除已选课程
    $sql = "delete from choose where student_no=$student_no and course_no=$course_no";
    mysql_query($sql);
    $affected_rows = mysql_affected_rows();
    close_connection();
    if ($affected_rows > 0)
        $message = "成功退选该课程！";
    else
        $message = "退选该课程失败！";
    header("Location:index.php?message=$message");
    return;
}
else
{
    $message = "您不是学生或者任课教师！";
    header("Location:index.php?message=$message");
    return;
}
?>

