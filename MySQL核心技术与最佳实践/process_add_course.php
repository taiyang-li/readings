<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php
include_once("database.php");

$course_name = $_POST["course_name"];    // 课程号
$up_limit = $_POST["up_limit"];          // 课程选课人数上限
$description = $_POST["description"];    // 课程描述
$teacher_no = $_POST["teacher_no"];      // 教师工号
$available = $up_limit;                   // 可选学生数 
$break = "<br/>";
echo $course_name . $break . $up_limit . $break . $description . $break . $teacher_no . $break . $available . $break; 
$insert_sql = "insert into course values(null, '$course_name', '$up_limit'," .  
              "to_english_fn('$description'), '未审核', '$teacher_no', '$available')";  
get_connection();
mysql_query($insert_sql);
$affected_rows = mysql_affected_rows();
close_connection();
if ($affected_rows > 0)
    $message = "课程添加成功";
else
    $message = "课程添加失败";
header("Location:index.php?message=$message");
?>
