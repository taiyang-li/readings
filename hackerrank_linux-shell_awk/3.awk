#!/bin/awk -f

{
    sum = 0
    for (i=2; i<=NF; ++i)
        sum += $i

    if (sum >= 80*(NF-1))
        print $1" : A"
    else if (sum >= 60*(NF-1))
        print $1" : B"
    else if (sum >= 50*(NF-1))
        print $1" : C"
    else
        print $1" : FAIL"
}
