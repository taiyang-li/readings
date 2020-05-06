create table profile
(
	id int unsigned not null auto_increment,
	name char(20) not null,
	birth date,
	color enum('blue', 'red', 'green', 'brown', 'black', 'white'),
	foods set('lutefisk', 'burrito', 'curry', 'eggroll', 'fadge', 'pizza'),
	cats int,
	primary key(id)
);

