<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php
include_once("database.php");
include_once("permission.php");
if (!is_admin())
{
    $message = "您不是管理员！";
    header("Location:index.php?message=$message");
    return;
}
else
{
    $sql = "select * from course_teacher_view where up_limit-available < 30";
    get_connection();
    $result_set = mysql_query($sql);
    $rows = mysql_num_rows($result_set);
    
    if ($rows == 0)
    {
        $message = "暂无信息！";      
        header("Location:index.php?message=$message");  
        return;
    }
    else
    {
        # 课号 课程名 人数上限 任课教师 联系方式 可选人数 课程状态 操作 
        echo "<table><tr><th>课号</th><th>课程名</th><th>人数上限</th><th>任课教师</th><th>联系方式</th><th>可选人数</th><th>课程状态</th><th>操作</th></tr>";
        while ($course_teacher = mysql_fetch_array($result_set))
        {
            echo "<tr>";
            $course_no = $course_teacher["course_no"];
            $course_name = $course_teacher["course_name"];
            $up_limit = $course_teacher["up_limit"];
            $teacher_name= $course_teacher["teacher_name"];
            $teacher_contact = $course_teacher["teacher_contact"];
            $available = $course_teacher["available"];
            $status = $course_teacher["status"];
            $description = $course_teacher["description"];

            echo "<td>" . $course_no . "</td>";
            echo "<td><a href='#' title=$description>" . $course_name . "</a></td>";
            echo "<td>" . $up_limit . "</td>";
            echo "<td>" . $teacher_name . "</td>";
            echo "<td>" . $teacher_contact . "</td>";
            echo "<td>" . $available . "</td>";
            echo "<td>" . $status . "</td>";
            echo "<td><a href=index.php?url=delete_course.php&course_no=$course_no>" . "删除该课程"  . "</a></td>";
            echo "</tr>";
        }
        echo "</table>";
    }
    close_connection();
}
?>
