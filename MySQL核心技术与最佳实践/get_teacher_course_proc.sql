use choose;
show tables;

drop procedure if exists get_teacher_course_proc;
delimiter $$
create procedure get_teacher_course_proc(in t_no char(11))
reads sql data
begin
    select course_no, course_name, teacher_name, teacher_contact, status, to_chinese_fn(description) description 
    from teacher join course 
    on course.teacher_no=teacher.teacher_no 
    where teacher.teacher_no=t_no;  
end
$$
delimiter ;
