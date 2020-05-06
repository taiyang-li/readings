#!/bin/awk -f

BEGIN {
   last_line = ""
}

{
    if (NR % 2 == 0)
        print last_line ";" $0
    last_line = $0
}
