#!/bin/bash
# �����ļ�ÿһ�У�����ÿ�е�ÿ�����ʣ�����ÿ�����ʵ�ÿ���ַ�

while read line; do
	for word in $line; do
		for((i=0; i<${#word}; i++)); do
			echo ${word:i:1}
		done
		echo 
		sleep 1
	done
done < awk.sh
