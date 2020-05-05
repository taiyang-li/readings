#!/bin/bash
# 使用uniq

if [ -e log ]; then 
	rm -f log
fi
touch log
echo "1" >> log
echo "2" >> log 
echo "3" >> log 
echo "4" >> log 
echo "4" >> log 

# 去除重复行
cat log | sort | uniq 

# 打印重复行数
cat log | sort | uniq -c 

# 打印重复行
cat log | sort | uniq -d 

# 打印不重复行
cat log | sort | uniq -u

# 计算字符个数
INPUT="KSLDHGLKGHEIGUEFDDIFH"
OUTPUT=`echo $INPUT | sed 's/[^\n]/&\n/g' | sed '/^$/d' | sort | uniq -c | tr -d "\n"`
echo $OUTPUT

