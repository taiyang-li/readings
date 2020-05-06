<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php
function is_login()
{
    if (empty($_SESSION["role"]))
        return false;
    else
        return true;
}

function is_student()
{
    if (is_login() && $_SESSION["role"] == "student")
        return true;
    else
        return false;
}

function is_teacher()
{
    if (is_login() && $_SESSION["role"] == "teacher")
        return true;
    else
        return false;
}

function is_admin()
{
    if (is_login() && $_SESSION["role"] == "admin")
        return true;
    else
        return false;
}
?>
