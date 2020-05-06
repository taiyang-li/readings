delimter $$ 
create function get_sum_fn(n int) returns int;	
begin 
	declare sum char(20) default 0;
	declare start int default 0;
	repeate 
		set start = start + 1;
		set sum = sum + start;
		until start = n;
	end repeat;
	return sum;
end
$$
delimeter;
