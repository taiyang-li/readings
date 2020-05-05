#!/bin/bash
# set -x 启动调试模式
# set +x 关闭调试模式 

for i in {1..6}; do
	set -x 
	echo $i
	set +x 
done
echo "finish."

