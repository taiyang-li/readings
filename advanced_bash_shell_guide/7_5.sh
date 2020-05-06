#!/bin/bash

a=4
b=5

echo 
if [ "$a" -ne "$b" ]; then 
	echo "$a is not euqal to $b"
	echo "(arithmetic comparsion)"
fi

echo 
if [ "$a" != "$b" ]; then
	echo "$a is not equal to $b"
	echo "(string comparision)"
fi

exit 0
