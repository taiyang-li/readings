#!/bin/bash

function show_usage
{
	echo "sh $0 <url"
	exit -1
}
if [ $# -lt 1 ]; then 
	show_usage
fi

svn info --username "<username>" --password "<passwd>" $1


