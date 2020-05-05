#!/bin/bash
# 生成文件统计信息

if [ $# -ne 1 ]; then 
	echo $0 basepath;
	echo
fi

path=$1
declare -a statarray;

while read line; do
	ftype=`file -b $line`
	((${statarray[$ftype]}++))
done < <(find $path -type f -print);

for ftype in ${!statarray[@]}; do
	echo "$ftype: ${statarray[$ftype]}"
done
