#!/bin/bash
# 使用tr 

# 替换
touch log
echo "12345" > log
cat log | tr "0123456789" "1234567890"

# 删除 
echo "hello, 123" >log
cat log | tr  -d "[0-9]"

# 补集
echo "hello, 123" > log
cat log | tr -d -c "[0-9\n]"

# 去除重复空格
echo "hello,  world" > log
cat log | tr -s " "

