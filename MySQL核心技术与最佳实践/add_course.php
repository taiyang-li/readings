<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/> 
<?php
include_once("permission.php");
if (!is_teacher())
{
    echo "请以教师身份登陆！";
    return;
}
$account_no = $_SESSION["account_no"];
?>	
<form action="process_add_course.php" method="post">
课程名： <input type="text" name="course_name">
上限：
<select name="up_limit">
<option value="60">60人上限</option>
<option value="150">150人上限</option>
<option value="230">230人上限</option>
</select>
<br/>
描述：<textarea name="description"></textarea><br/>
工号：<input type="text" name="teacher_no" value="<?php echo $account_no; ?>"  readonly>
<br/>
<input type="submit" value="添加课程"/> 
<input type="reset" value="重填"/>
</form>

