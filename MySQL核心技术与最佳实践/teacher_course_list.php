<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php
include_once("database.php");
include_once("permission.php");
if (!is_teacher())
{
    $message = "您不是教师";
    header("Location:index.php?message=$message");
    return;
}
else
{
    $account_no = $_SESSION["account_no"];
    get_connection();  
    $sql = "call get_teacher_course_proc('$account_no')";
    $result_set = mysql_query($sql);
    $rows = mysql_affected_rows();
	
    if ($rows == 0)
    {
        $message = "您暂时没有申报课程";
        header("Location:index.php?message=$message");
        return;
    }
    else
    { 
        echo "<table><tr> <th>课号</th> <th>课程名</th> <th>任课教师</th> <th>联系方式</th> <th>状态</th> <th>操作</th> </tr>";
        while ($course_teacher = mysql_fetch_array($result_set))
        {
            echo "<tr>";  
            $course_no = $course_teacher["course_no"];
            $course_name = $course_teacher["course_name"];
            $teacher_name = $course_teacher["teacher_name"];
            $teacher_contact = $course_teacher["teacher_contact"];
            $description = $course_teacher["description"];
            $status = $course_teacher["status"];
            echo "<td>" . $course_no . "</td>";
            echo "<td><a href='#' title=$description>" . $course_name . "</a></td>";
            echo "<td>" . $teacher_name . "</td>";
            echo "<td>" . $teacher_contact . "</td>";
            echo "<td>" . $status . "</td>";
            if ($status == "未审核")
                echo "<td><a href='index.php?url=delete_course.php&course_no=$course_no'>删除该课程</a></td>";
            else
                echo "<td><a href='index.php?url=course_student_list.php&course_no=$course_no'>查看学生信息</a></td>";
            echo "</tr>";
        }
        echo "</table>";
    }
    close_connection();
}
?>
