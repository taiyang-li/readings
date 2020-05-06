#!/bin/bash

function show_usage()
{
    echo "./$0 <sql>"
    exit -1
}

if [ $# -lt 1 ]; then 
    show_usage
fi

sql=$1
count=0
queryids=""
for queryid in `cat ./queryid.txt`; do
    if [ -z $queryids ]; then
        queryids="${queryid}"
    else
        queryids="${queryids},${queryid}"
    fi
    
    ((count++))
    ((tmp = count % 100))
    if [ $tmp -eq 0 ]; then
        queryids="(${queryids})"
        echo $sql $queryids ";"
        queryids=""
    fi
done
