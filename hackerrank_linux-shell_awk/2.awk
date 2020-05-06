#!/bin/awk -f

{
    is_fail = 0
    for (i=2; i<=NF; ++i)
    {
        if ($i < 50)
        {
            is_fail = 1
            break
        }
    }

    if (is_fail == 1)
    {
        print $1" : Fail"
    }
    else
    {
        print $1" : Pass"
    }
}
