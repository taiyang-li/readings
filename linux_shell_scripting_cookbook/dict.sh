#!/bin/bash
# ������뵥���Ƿ��ڵ����б���

word=$1
grep -P -q "^$word$" /usr/share/dict/words 
if [ $? -eq 0 ]; then 
	echo "$word is a dictionary word"
else
	echo "$word is not a dictionary word"
fi
