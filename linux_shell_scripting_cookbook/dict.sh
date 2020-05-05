#!/bin/bash
# 检查输入单词是否在单词列表内

word=$1
grep -P -q "^$word$" /usr/share/dict/words 
if [ $? -eq 0 ]; then 
	echo "$word is a dictionary word"
else
	echo "$word is not a dictionary word"
fi
