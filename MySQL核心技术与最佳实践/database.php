<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/> 
<?php
$database_connection = null;
# 连接数据库文件 
function get_connection()
{
    $hostname = "localhost";
    $database = "choose";
    $username = "root";
    $password = "root";
    global $database_connection;
    $database_connection = @mysql_connect($hostname, $username, $password) or exit(mysql_error());
	
	mysql_query("set name 'gbk'");
	
    @mysql_select_db($database, $database_connection) or exit(mysql_error());
	
	# 设置字符编码
	mysql_query("set names 'utf8' ");          
    mysql_query("set character_set_client=utf8");  
    mysql_query("set character_set_results=utf8"); 
}

function close_connection()
{
    global $database_connection;
    $database_connection = null;
}
?>
