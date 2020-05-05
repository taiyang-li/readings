#!/bin/bash
# 使用sort

if [ -e data.txt ]; then 
	rm -f data.txt
fi
touch data.txt
echo "1 max 2000" >> data.txt
echo "2 winxp 4000" >> data.txt
echo "3 bsd 1000" >> data.txt
echo "4 linux 1000" >> data.txt

# 按照字符串排序
cat data.txt | sort 

# 将排序结果输出到文件
cat data.txt | sort -o log

# 按照数字排序
cat data.txt | sort -n

# 按照第二列进行排序
cat data.txt | sort -k 2

# 按照第一列进行逆序排序
cat data.txt | sort -nk 1


