<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php
include_once("database.php");
include_once("permission.php");
if (!is_student())
{
    $message = "您不是学生";
    header("Location:index.php?message=$message");
    return;
}
else
{
    $account_no = $_SESSION["account_no"];
    get_connection();
    $sql = "call get_student_course_proc('$account_no')";
    $result_set = mysql_query($sql);
    $rows = mysql_affected_rows();
	// echo $rows; 	
    if ($rows == 0)
    {
        $message = "您暂时没有选课";
        header("Location:index.php?message=$message");
        return;
    }
    else
    {
        echo "<table> <tr> <th>课号</th> <th>课程名</th> <th>任课教师</th> <th>联系方式</th> <th>操作</th> </tr>";
        while ($course_student = mysql_fetch_array($result_set))
        {
            echo "<tr>";
            $course_no = $course_student["course_no"];
            $course_name = $course_student["course_name"];
            $teacher_name = $course_student["teacher_name"];
            $teacher_contact = $course_student["teacher_contact"];
            $description = $course_student["description"];
            echo "<td>" . $course_no . "</td>";
            echo "<td><a href='#' title=$description>" . $course_name . "</a></td>";
            echo "<td>" . $teacher_name . "</td>";
            echo "<td>" . $teacher_contact . "</td>";
            echo "<td><a href='index.php?url=quit_course.php&course_no=$course_no'>取消选修该课程</a> <a href='index.php?url=course_list.php&c_before=$course_no'>调换该课程</a></td>";
            echo "</tr>";
        }
        echo "</table>";
    }
    close_connection();
}
?>

