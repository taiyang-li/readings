# print report table 
define print_re_table 
    if $argc == 1
        set $i = 0
        set $size = $arg0->row_count()
        while $i < $size 
            p $arg0->_rows[$i]->to_string()
            set $i++
        end
    end
end
