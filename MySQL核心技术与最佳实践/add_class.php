<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/> 
<?php
include_once("permission.php");
if (!is_admin())
{
    echo "请以管理员身份登录！";
    return;             # 说好的跳转呢 
}
?>

<form action = "process_add_class.php" method = "post">
班级名：<input type="text" name="class_name"/><br/>
院系名：
<select name="department_name">
<option value="信息工程学院" selected>信息工程学院</option>
<option value="机电工程学院">机电工程学院</option>
</select>
<br/>
<input type="submit" value="添加班级"/>
<input type="reset" value="重填"/>
</form>

