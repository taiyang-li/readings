#!/bin/bash

MAXCOUNT=10
count=1

echo 
echo 
echo "$MAXCOUNT random numbers: "
echo "------------------------"
while [ "$count" -le $MAXCOUNT ]; 
do
	number=$RANDOM
	echo $number
	let "count += 1"
done
echo "------------------------"

RANGE=500
echo 
number=$RANDOM
let "number %= $RANGE"
echo "random number lesser than $RANGE ---- $number"
echo

FLOOR=200
number=0
while [ "$number" -le $FLOOR ]
do
	number=$RANDOM
done
echo "random number greater than $FLOOR -- $number"
echo 

number=0
while [ "$number" -le $FLOOR ]
do
	number=$RANDOM
	let "number %= $RANGE"
done
echo "random number between $FLOOR and $RANGE --- $number"
echo 
