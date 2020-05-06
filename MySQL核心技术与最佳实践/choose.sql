set character_set_database = utf8;
set character_set_server = utf8;
set character_set_client = utf8;
set character_set_connection = utf8;
set character_set_results = utf8;

drop database if exists choose;
create database choose default character set utf8 collate utf8_unicode_ci; 
show databases;
use choose;

drop table if exists admin; 
create table admin 
(
    admin_no char(10) character set utf8 collate utf8_unicode_ci not null primary key,
    password char(32) not null,
    admin_name char(20) character set utf8 collate utf8_unicode_ci not null
) character set utf8 collate utf8_unicode_ci;
insert into admin values('admin', md5('admin'), 'administrator');
show tables;


drop table if exists  teacher; 
create table teacher  -- 教师表 (编号 姓名 联系方式)
( 
	teacher_no char(10) character set utf8 collate utf8_unicode_ci primary key,      
    password char(32) character set utf8 collate utf8_unicode_ci not null,
	teacher_name char(10)  character set utf8 collate utf8_unicode_ci not null,   
	teacher_contact char(20)  character set utf8 collate utf8_unicode_ci not null
) engine = InnoDB default character set utf8 collate utf8_unicode_ci;
show tables;

drop table if exists  classes; 
create table classes    -- 班级表 (编号 名称 院系) 
(
	class_no int auto_increment primary key,
	class_name char(20) character set utf8 collate utf8_unicode_ci not null unique,
	department_name char(20) character set utf8 collate utf8_unicode_ci not null
) engine = InnoDB  default character set utf8 collate utf8_unicode_ci;
show tables;

drop table if exists course; 
create table course  -- 课程表(编号 名称 人数上限 描述 状态 教师编号)
(
    course_no int auto_increment primary key,  -- 课程名随着插入自动形成 
	course_name char(20) character set utf8 collate utf8_unicode_ci not null,        
	up_limit int default 60,
	description text character set utf8 collate utf8_unicode_ci,
    status char(10)  character set utf8 collate utf8_unicode_ci default '未审核' ,
	teacher_no char(10) character set utf8 collate utf8_unicode_ci  not null unique, 
    available int default 60 ,
	constraint course_teacher_fk foreign key(teacher_no) references teacher(teacher_no)
) engine = InnoDB  default character set utf8 collate utf8_unicode_ci;
show tables;

drop table if exists student;
create table student             -- 学生表 (学号 姓名 联系方式  班号) 
(
	student_no char(11) primary key,
    password char(32) character set utf8 collate utf8_unicode_ci not null,
	student_name char(10) character set utf8 collate utf8_unicode_ci not null,
	student_contact char(20) character set utf8 collate utf8_unicode_ci not null,
	class_no int,
	constraint student_class_fk foreign key(class_no) references classes(class_no) 
) engine = InnoDB  default character set utf8 collate utf8_unicode_ci;
show tables;

drop table if exists choose; 
create table choose              -- 选课表 (选课编号 学号 课程号 得分)
(	
	choose_no int auto_increment primary key,
	student_no char(11) character set utf8 collate utf8_unicode_ci not null,
	course_no int not null,
	score tinyint unsigned,
	choose_time datetime not null,
	constraint choose_student_fk foreign key(student_no) references student(student_no),
	constraint choose_course_fk foreign  key(course_no) references course(course_no)
) engine = InnoDB  default character set utf8 collate utf8_unicode_ci;
show tables;

drop function if exists to_chinese_fn;  
delimiter $$
create function to_chinese_fn(s varchar(32760)) returns varchar(32760)
no sql
begin
    declare new_string varchar(32760);
    declare temp_string varchar(32760);
    set temp_string = replace(s, ' H', '');
    set temp_string = replace(temp_string, 'H', '');
    set temp_string = unhex(temp_string);
    return temp_string;
end
$$
delimiter ;

delimiter $$
create function to_english_fn(s varchar(32760)) returns varchar(32760)
no sql
begin
    declare start int;
    declare string_length int;
    declare new_string varchar(32760);
    declare temp_string varchar(32760);
    set start = 1;
    set string_length = char_length(s);
    set new_string = '';
    
    while start <= string_length do 
        set temp_string = hex(substring(s, start, 1)); 
        set start = start + 1;
        set new_string = concat(new_string, ' H', temp_string);
    end while;
    return trim(new_string);
end
$$
delimiter ; 

drop view if exists course_teacher_view; 
create view course_teacher_view as
select course_no, course_name, up_limit, to_chinese_fn(description) description, teacher.teacher_no, teacher_name, teacher_contact, available, status from course join teacher on course.teacher_no=teacher.teacher_no;
show tables;

drop procedure if exists choose_proc; 
delimiter $$
create procedure choose_proc(in s_no char(11), in c_no int, out state int) 
modifies sql data     --s_no 学号  c_no 课程号 state 输出状态
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


drop procedure if exists get_course_student_proc; 
delimiter $$
create procedure get_course_student_proc(in c_no int)
reads sql data
begin
    select department_name, class_name, student.student_no, student_name, student_contact
    from student
    join classes on student.class_no = classes.class_no
    join choose on student.student_no = choose.student_no
    where course_no = c_no
    order by department_name, class_name, student_name; 
end
$$
delimiter ; 

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
            update course set available = available-1 where course_no=c_before;
            update course set available = available+1 where course_no=c_after;
            set state = c_after;
            -- 改变course的available值
        end if;
        commit;
    end if;
end
$$
delimiter ;


