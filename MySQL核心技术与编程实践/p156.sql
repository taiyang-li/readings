delimeter $$
create function get_week_fn(week_no int) returns char(20)
no sql
begin
	declare week char(20);
	case week_no
		when 0 then set week = 'monday';
		when 1 then set week = 'tuesday';
		when 2 then set week = 'wedsday';
		when 3 then set week = 'thursday';
		when 4 then set week = 'friday';
		when 5 then set week = 'satureday';
		when 6 then set week = 'sunday';
		else
			set week = 'breakday';
	end case;
	return week;
end
$$ 
delimeter;

