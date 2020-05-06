#!/bin/bash

function show_usage
{
	echo "sh $0 <src-url> <dst-url> <comment>"
	exit -1
}
if [ $# -lt 3 ]; then 
	show_usage
fi

svn cp --username "<username>" --password "<passwd>" $1 $2 -m"$3"
exit 0;


