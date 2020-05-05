#!/bin/bash

if [ $# -ne 1 ]; then 
	echo "Usage: $0 filename"
	exit -1
fi

filename=$1

grep -P -o "\b\w+\b" $filename | awk '{count[$0]++} END{printf("%-14s%s\n", "Word", "Count"); for (i in count) {printf("%-14s%s\n", i, count[i]);}}' 
