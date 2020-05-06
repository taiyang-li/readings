delimeter $$
create function get_name_fn (no int, role char(20)) returns char(20)
reads sql data 
begin 
	declare name char(20);  
	if ('student' = role ) then 
		select student_name into name from student where student_no = no;
	elseif ('teacher' = role) then 
		select teacher_name into name from teacher where teacher_no = no;
		select 
	end if; 
	return name;
end
$$ 
delimeter;
