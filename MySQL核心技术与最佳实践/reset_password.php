<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php
# type name value 注意区别
include_once("permission.php");
if (!is_admin())
{
    echo "请以管理员身份登陆！";
    return;
}
?>

<form action="process_reset_password.php" method="post">
账号：<input type="text" name="account_no"/><br/>
新密码：<input type="text" name="password"/><br/>
角色：<select name="role">
<option value="student" selected>学生</option>
<option value="teacher">教师</option>
</select>
<br/>
<input type="submit" value="密码重置"/>
<input type="reset" value="重填"/>
</form>
