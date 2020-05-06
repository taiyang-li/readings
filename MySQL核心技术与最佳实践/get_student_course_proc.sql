use choose;
drop procedure if exists get_student_course_proc;  
delimiter $$
create procedure get_student_course_proc(in s_no char(11))
reads sql data
begin
    select choose.course_no, course.course_name, teacher_name, teacher_contact, to_chinese_fn(description) description
    from choose 
	join course on course.course_no=choose.course_no 
	join teacher on teacher.teacher_no=course.teacher_no 
	where student_no=s_no;
end
$$
delimiter ;