use choose;
drop procedure if exists choose_proc; 
delimiter $$
create procedure choose_proc(in s_no char(11), in c_no int, out state int) 
modifies sql data    
begin
    declare s1 int;
    declare s2 int;
    declare s3 int;
    declare status1 char(10);
    
    set state = 0;
    set status1 = '未审核'; 

    select count(*) into s1 from choose where student_no=s_no and course_no=c_no;
    if (s1 >= 1)    then    -- 是否学生已经选过该课  
        set state=-1;
    else
        select count(*) into s2 from choose where student_no=s_no;   
        if (s2 >=2)  then  -- 是否学生已经选过超过两门的课
            set state=-2;
        else
            select status into status1 from course where course_no = c_no;
            select available into s3 from course where course_no = c_no;
			
            if (status1 = "未审核" || s3 = 0) then   
                set state = -3;   
            else
                insert into choose values(null, s_no, c_no, null, now()); 
                set state = last_insert_id();  -- 本次操作的ID 
            end if;
        end if;
    end if;
end
$$
delimiter ;
