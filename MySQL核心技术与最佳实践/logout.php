<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php
session_unset();           # 删除web服务器内存和文件中的SESSION信息
session_destroy();         # 删除web服务器的session文件 
header("Location:index.php?message=注销成功！");   # 重定向到首页 
?>

