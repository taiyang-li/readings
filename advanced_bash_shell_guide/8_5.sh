#!/bin/bash

a=24
b=47

if [ "$a" -eq 24 ] && [ "$b" -eq 47 ]; then 
	echo "test #1 success"
else
	echo "test #1 failed"
fi

if [ "$a" -eq 98 ] || [ "$b" -eq 47 ]; then 
	echo "test #2 success"
else
	echo "test #2 failed"
fi

if [ "$a" -eq 24 -a "$b" -eq 47 ]; then 
	echo "test #3 success"
else
	echo "test #3 failed"
fi

if [ "$a" -eq 98 -o "$b" -eq 47 ]; then 
	echo "test #4 success"
else
	echo "test #4 failed"
fi

a=rhino
b=crocodile
if [ "$a" = rhino ]  && [ "$b" = crocodile ]; then 
	echo "test #5 success"
else
	echo "test #5 fail"
fi

exit 0
