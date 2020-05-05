#!/bin/bash

if [ $# -ne 2 ]; then 
	echo "Usage: $0 filename sring_length"
	exit -1
fi

filename=$1
count=$(($2/2))
basepattern='/^'
for ((i=0; i<$count; i++)); do
	basepattern=$basepattern'\(.\)'
done

if [ $(($2%2)) -ne 0 ]; then 
	basepattern=$basepattern'.'
fi

for ((count; count>0; count--)); do
	basepattern=$basepattern'\'"$count"
done
basepattern=$basepattern'$/p'
echo $basepattern
sed -n "$basepattern" $filename
