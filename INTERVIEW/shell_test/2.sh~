#!/bin/bash

if [ -z "$myvar" ] 
then
	echo "myvar is not defined"
fi

myvar="3"
if [ "$myvar" -eq 3 ]
then
	echo "myvar = 3"
fi

if [ "$myvar" = "3"  ]
then 
	echo "myvar equals 3"
fi



myvar="foo bar oni"
if [  "$myvar" = "foo bar oni"  ]
then 
	echo "yes"
fi


for x in "one" "two" "three" "four"
do
	echo number $x
done

for x in one two three four
do
	echo number $x
done


for myfile in /etc/r*
do
	if [  -d "$myfile" ]
	then 
		echo "$myfile (dir)"
	else
		echo "$myfile"
	fi
done


for x in ../network/*
do
	echo "$x is a file"
done


for thing in "$@"
do 
	echo "you typed $thing" 
done

