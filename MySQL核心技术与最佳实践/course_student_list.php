<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/> 
<?php
include_once("permission.php");
include_once("database.php");
get_connection();   
$course_no = $_GET["course_no"];  // 从跳转指令得到course_no

# 如果是教师，检查该教师是不是这门课的老师   
if (is_teacher())
{
    $teacher_no = $_SESSION["account_no"];   // 从固有cookie中得到账号  
    $select_sql = "select course_no from course where course_no=$course_no and teacher_no = $teacher_no";
    $result_set = mysql_query($select_sql);  
    if (mysql_num_rows($result_set) == 0)  
    {
        $message = "您不是任课教师！";  
        header("Location:index.php?message=$message");
        return;
    }
}

if (is_admin() || is_teacher())
{
    $sql = "call get_course_student_proc($course_no)";
    $result_set = mysql_query($sql);
    $rows = mysql_num_rows($result_set);
    if ($rows == 0)
    {
        $message =  "这门课程暂无学生选修！";
        header("Location:index.php?message=$message");
        return;
    }
    else      # 显示一门课所有学生信息
    {
        # 院系 班级 学号 学生姓名 联系方式 操作
        echo "<table><tr><th>院系</th><th>班级</th><th>学号</th><th>学生姓名</th><th>联系方式</th><th>操作</th></tr>";
        while ($student = mysql_fetch_array($result_set))
        {
            echo "<tr>";
            $department_name = $student["department_name"];
            $class_name = $student["class_name"];
            $student_no = $student["student_no"]; 
            $student_name = $student["student_name"];
            $student_contact = $student["student_contact"];
            echo "<td>" . $department_name . "</td>";
            echo "<td>" . $class_name . "</td>";
            echo "<td>" . $student_no . "</td>";
            echo "<td>" . $student_name . "</td>";
            echo "<td>" . $student_contact . "</td>";
            echo "<td><a href='index.php?url=quit_course.php&student_no=$student_no&course_no=$course_no'>取消该学会的选课</a></td>"; 
            echo "</tr>";
        }
        echo "</table>";
    }    
    close_connection(); 
}
else
{
    $message = "您无权查看！";
    header("Location:index.php?message=$message");
    return;
}
?>
