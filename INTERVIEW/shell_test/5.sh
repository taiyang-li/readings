#!/bin/bash

myvar="hello"

myfunc()
{
	myvar="one two three"
	for x in $mvar
	do
		echo $x
	done
}


myfunc 
echo $myvar $x
