<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/> 
<?php
include_once("permission.php");
include_once("database.php");

# 赶走非学生 
if (!is_student())
{
    $message = "您无权选修课程！<br/>";
    header("Location:index.php?message=$message");
    return;
}
else
{
    $account_no = $_SESSION["account_no"];  
    $c_after = $_GET["c_after"];     
	$c_before = $_GET["c_before"]; 
	/* 
	echo $c_before;            
	echo " ";
	echo $c_after; 
	*/ 
    if ($c_before == "empty") # 选课  如果c_before
    {
		// echo "选课";
        $sql = "call choose_proc('$account_no', '$c_after', @state)";
    } 
    else     # 调课   
    {
		// echo "调课"; 
        $c_before = $_GET["c_before"];
        $sql = "call replace_course_proc('$account_no', '$c_before', '$c_after', @state)";
    }

    get_connection();  	
	mysql_query("set @state = 0;");      // 首先初始化输出
    mysql_query($sql);                   // 将选课信息插入数据库 
	$result_set = mysql_query("select @state as state");  // 选取表格信息
    $result = mysql_fetch_array($result_set);             // 取出一行数据    
    $state = $result["state"];                            //  
	 
	/*
	mysql_query("set @hehe = 0;");
	$sql = "select count(*) into @hehe from choose where student_no = $account_no"; 
	mysql_query($sql);
	$result_set = mysql_query("select @hehe as hehe");  // 选取表格信息
    $result = mysql_fetch_array($result_set);             // 取出一行数据 
	$hehe = $result["hehe"];
	echo " " . $hehe;
	*/ 
	if ($state == -1)      
        $message = "您已经修过这门课程"; 
    elseif($state == -2)
        $message = "您已经选修了两门课程";
    elseif($state == -3)
        $message = "课程已经报满，请选择其他课程";
    else 
        $message = "您已经成功地选修了这门课程";
	close_connection();
    header("Location:index.php?message=$message");
}
?>

