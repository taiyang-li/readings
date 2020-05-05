#!/bin/bash
# 使用xargs进行批量操作 

if [ -e ./log ]; then
	rm -rf ./log
fi


touch log
echo "1 2 3" >> log
echo "9 8 7 6 3 6" >> log 

cat log | xargs

cat log | xargs -0

cat log | xargs -n 3

cat log | xargs -n 1 | xargs -I  {} seq 1 {}

touch 1.log 2.log 3.log
find . -name "*.log" -print0 | xargs -0 rm -f
