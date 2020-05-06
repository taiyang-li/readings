#!/bin/bash

SUCCESS=0
E_NOARGS=65

if [ -z $1 ]; then 
	echo "usage: `basename $0` rpm-file" 
	exit $E_NOARGS
fi

{
	echo 
	echo "archive description:"
	rpm -qpi $1
	echo 
	echo "archive listing:"
	rpm -qpl $1
	echo 
	rpm -i --test $i
	if [ $? -eq $SUCCESS ]; then 
		echo "$1 can be installed"
	else
		echo "$1 cannot be installed"
	fi
	echo 
} > "$1.test"

echo "results of rpm test in file $1.test"
exit 0
