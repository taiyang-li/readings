use choose;



create table teacher
(
	teacher_no char(10) primary key,
	teacher_name char(10) not null,
	teacher_contact char(20) not null
) engine = InnoDB default charset=gbk;



create table classes
(
	class_no int auto_increment primary key,
	class_name char(20) not null unique,
	department_name char(20) not null
) engine = InnoDB default charset=gbk;



create table course
(
	course_no int auto_increment primary key,
	course_name char(20) not null,
	up_limit int default 60,
	description text not null,
	status char(6)  default 'prepare',
	teacher_no char(20) not null unique,
	constraint course_teacher_fk foreign key(teacher_no) references teacher(teache_no)
) engine = InnoDB default charset=gbk;


create table student 
(
	student_no char(11) primary key,
	student_name char(10) not null,
	student_contact char(20) not null,
	class_no int,
	constraints student_class_fk foreign key(class_no) references classes(class_no) 
) engine = InnoDB default charset=gbk;

create table choose
(	
	choose_no int auto_increment primary key,
	student_no char(11) not null,
	course_no int not null,
	score tinyint unsigned,
	choose_time datetime not null,
	constraints choose_student_fk foreign key(student_no) references student(student_no),
	constraints choose_course_fk foreign  key(course_no) references course(course_no)
) engine = InnoDB default charset=gbk;






