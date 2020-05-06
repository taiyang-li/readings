delimter $$ 
create function get_sum_fn(n int) returns int;	
begin 
	declare sum char(20) default 0;
	declare start int default 0;
	add_sum: loop  
		set start = start + 1;
		set sum = sum + start;
		if (start = n)
			leave add_sum;
		end if;
	end loop;
	return sum;
end
$$
delimeter;
