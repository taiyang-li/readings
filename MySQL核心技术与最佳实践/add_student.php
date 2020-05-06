<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<form action="process_add_student.php" method="post">
学号：<input type="text" name="student_no"/><br/>
密码：<input type="text" name="password"/><br/>
确认密码：<input type="text" name="re_password"/><br/>
姓名：<input type="text" name="student_name"/><br/>
联系方式：<input type="text" name="student_contact"/><br/>
班级：
<select name="class_id">
<?php
header("content-type:text/html; charset=utf-8"); 
include_once("database.php");
get_connection();
$sql = "select * from classes";
mysql_query("set names 'big5'");
$result_set = mysql_query($sql);
close_connection();
while ($row = mysql_fetch_array($result_set))
{
?>
    <option value="<?php echo $row['class_no'];?>">
	<?php 
	echo $row['class_name'];
	?>
	</option>
<?php
}
?>
</select>
<br/>
<input type="submit" value="注册"/>
<input type="reset"  value="重填"/>
</form>
