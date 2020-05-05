#!/bin/bash
# 遍历文件每一行，遍历每行的每个单词，遍历每个单词的每个字符

while read line; do
	for word in $line; do
		for((i=0; i<${#word}; i++)); do
			echo ${word:i:1}
		done
		echo 
		sleep 1
	done
done < awk.sh
