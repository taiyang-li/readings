use choose;
drop procedure if exists replace_course_proc;  
delimiter $$
create procedure replace_course_proc(in s_no char(11), in c_before int, in c_after int, out state int)
modifies sql data
begin 
    declare s int;
    declare status1 char(10);
    
    set state = 0;
    set status1 = '未审核';

    if (c_before=c_after)  then 
        set state = -1;
    else
        start transaction;
        -- 判断课程是否通过审核
        -- 判断课程是否可选
        select status into  status1 from course where course_no=c_after;
        select available into s from course where course_no=c_after;
        if (status1 = '未审核' || s = 0)  then 
            set state = -2;
        else
            -- 从choose删除旧课程  
            -- 从choose中添加新课程
            update choose set course_no=c_after, choose_time=now() where student_no=s_no and course_no=c_before; 
            -- 改变course的available值
            update course set available = available+1 where course_no=c_before;
            update course set available = available-1 where course_no=c_after;
            set state = c_after;
            -- 改变course的available值
        end if;
        commit;
    end if;
end
$$
delimiter ;

