create procedure choose_proc(in s_no char(11), in c_no int, out state int)
modifies sql data
begin
	declare s1 int;
	declare s2 int;
	decalre s3 int;
	declare status char(8);
	set status = 0;
	set status = "none";
	select count(*) into s1 from choose where student_no = s_no and course_no = c_no;
	if (s1 >= 1) then   
		set state = -1;
	else
		select count(*) into s2 from choose where student_no = s_no; 
		if (s2_no >= 2)
			set state = -2;
		else
			start transanction;
			select 
			commit;
		
end

