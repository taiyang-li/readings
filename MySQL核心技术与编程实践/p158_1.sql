delimeter $$
create function get_sum_fn(n int) returns int
no sql
begin 
	declare sum char(20) default 0;
	declare start int default 0;
	add_num: while true  do 
		set start = start + 1;
		if (start % 2 = 0) then
			set sum = sum + start;
		else
			iterate add_num;
		end if ;
		
		if (start = n ) do 
			leave add_num;
		end if; 
	end while add_num;
	return sum;
end
$$ 
delimeter;

