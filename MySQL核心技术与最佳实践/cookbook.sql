drop table if exists limbs;
create table limbs
(
	thing varchar(20),
	legs int,
	arms int
);
insert into limbs(thing, legs, arms) values('human', 2, 2);
insert into limbs(thing, legs, arms) values('insect', 6, 0);
insert into limbs(thing, legs, arms) values('squid', 0, 10);
insert into limbs(thing, legs, arms) values('octopus', 0, 8);
insert into limbs(thing, legs, arms) values('fish', 0, 0);
insert into limbs(thing, legs, arms) values('centipede', 100, 0);
insert into limbs(thing, legs, arms) values('table', 4, 0);
insert into limbs(thing, legs, arms) values('armchair', 4, 2);
insert into limbs(thing, legs, arms) values('phonograph', 0, 1);
insert into limbs(thing, legs, arms) values('tripod', 3, 0);
insert into limbs(thing, legs, arms) values('peg leg pete', 1, 2);
insert into limbs(thing, legs, arms) values('space alien', null, null);
insert into limbs(thing, legs, arms) values('computer', 0, 0);
