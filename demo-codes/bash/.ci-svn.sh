#!/bin/bash

function show_usage
{
	echo "sh $0 <comment>"
	exit -1
}
if [ $# -lt 1 ]; then 
	show_usage
fi

svn ci --username "<username>" --password "<passwd>" -m"$1"
exit 0;


