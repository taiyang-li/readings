delimeter $$
create function get_sum_fn(n int) returns int
no sql
begin 
	declare sum char(20) default 0;
	declare start int default 0;
	while start < n do 
		set start = start + 1;
		set sum = sum + start;
	end while;
	return sum;
end
$$ 
delimeter;
