#!/bin/bash 

n=1
echo -n "$n "

let "n = $n + 1"
echo -n "$n "

(( n = $n + 1 ))
echo -n "$n "

n=$(( $n+1 ))
echo -n "$n "

: $[ n = $n + 1 ]
echo -n  "$n "

let "n++"
echo -n "$n "

(( n++ ))
echo -n "$n "

: $(( n++ ))
echo -n "$n "

: $[ n++ ]
echo -n "$n "

echo 
exit 0


