<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/> 
<form action="index.php?url=course_list.php" method="post">
请输入关键字：<input type="text" name="keyword"/>
<input type="submit" value="全文检索">
</form>

<?php
include_once("permission.php");
include_once("database.php"); 
get_connection();

# 构建全文检索的关键字
if (!empty($_POST["keyword"])) 
{
    $keyword = $_POST["keyword"];  
    $keyword_result = mysql_query("select to_english_fn('$keyword') keyword");
    $keyword_array = mysql_fetch_array($keyword_result);
    $keyword = $keyword_array["keyword"]; 
}
if (!is_login() || is_student() || is_teacher())
{
    $sql = "select * from course_teacher_view where status='已审核'";
    if (!empty($keyword))
    {
        $sql = $sql . " and course_no in (select course_no from course where match (description) against ('$keyword'))";
    }
}
else if (is_admin())
{
    $sql = "select * from course_teacher_view";
    if (!empty($keyword))
    {
        $sql = $sql . " where course_no in (select course_no from course where match (description) against ('$keyword'))";
    }
}

$result_set = mysql_query($sql);
$rows = mysql_num_rows($result_set);

if ($rows == 0) 
{
    echo "暂无课程记录";
    return;
}

echo
"
<table>
<tr> 
<th>课号</th>  <th>课程名</th> <th>人数上限</th> <th>任课教师</th> <th>联系方式</th> <th>可选人数</th> <th>课程状态</th> <th>操作</th>
</tr>
";


# 遍历结果集
while ($course_teacher = mysql_fetch_array($result_set))
{
    echo "<tr>";
    $course_no = $course_teacher["course_no"];
    $course_name = $course_teacher["course_name"];
    $description = $course_teacher["description"];
    $status = $course_teacher["status"];
    echo "<td>" . $course_no . "</td>";
    echo "<td><a href='#' title=$description>" . $course_name . "</a></td>";
    echo "<td>" . $course_teacher["up_limit"] . "</td>";
    echo "<td>" . $course_teacher["teacher_name"] . "</td>";
    echo "<td>" . $course_teacher["teacher_contact"] . "</td>";
    echo "<td>" . $course_teacher["available"] . "</td>";
    echo "<td>" . $status . "</td>";
    if (is_admin())
    {
        if ($status == "未审核")  # 可删除 可通过
        {
            echo "<td bgcolor='#f0f0f0'><a href=index.php?url=check_course.php&course_no=$course_no>" . "通过审核" . "</a> <a href=index.php?url=delete_course.php&course_no=$course_no>" . "删除该课程" . "</a></td>";
        }
        else       # 可查看 可取消
        {
            echo "<td><a href=index.php?url=quit_check_course.php&course_no=$course_no>" . "取消审核" . "</a> <a href=index.php?url=course_student_list.php&course_no=$course_no>" . "查看学生信息" . "</a></td>";
        }
        
    }
    elseif (is_student()) 
    {
        $account_no = $_SESSION["account_no"];
        if (isset($_GET["c_before"]))
		{
			// echo "调课！"; 
            $c_before = $_GET["c_before"];  
		}
        else
		{
			// echo "选课";
            $c_before = "empty"; 
		}
		/*
		echo $c_before;
		echo "<br/>";
		echo $course_no;
		*/
        echo "<td><a href='index.php?url=choose_course.php&c_after=$course_no&c_before=$c_before'>选修该课程</a></td>";
    }
    else
        echo "<td>暂时无法操作</td>";
    echo "</tr>";
}
close_connection();
?>

