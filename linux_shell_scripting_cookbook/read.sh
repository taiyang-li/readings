#!/bin/bash
# 从用户输入读取6位密码

read -s -n 6 -t 10 -p "please input passwd whose len is 6:" passwd
echo 
if [ "$passwd"x == "123456"x ]; then 
	echo "input right"
else
	echo "input wrong"
fi

