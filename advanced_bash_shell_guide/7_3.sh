#!/bin/bash

linkchk()
{
	for element in $1/*; do 
		if [ -h $element -a ! -e $element ]; then 
			echo $element
		fi
		[ -d $element ] && linkchk $element
	done
}


# 实现了一个if else
[ $# -eq 0 ] && directorys=`pwd` || directorys=$@
for directory in $directorys; do 
	if [ -d $directory ]; then 
		linkchk $directory
	else
		echo "$direcoty is not a directory"
		echo "usage: $0 dir1 dir2 ..."
	fi
done
exit $?

