#!/bin/bash
# ¹şÏ£±í 

declare -a map
map[1]=liyang
map[2]=liuyuan

echo ${map[1]}
echo ${map[2]}

# ±éÀú¹şÏ£±í
echo -en "\e[42m"
printf "%-10s\t%-10s\n" key value
echo -e -n "\e[0m"
for key in ${!map[@]}; do
	printf "%-10s\t%-10s\n" $key ${map[$key]}
done

