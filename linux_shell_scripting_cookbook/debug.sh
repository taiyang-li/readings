#!/bin/bash
# set -x ��������ģʽ
# set +x �رյ���ģʽ 

for i in {1..6}; do
	set -x 
	echo $i
	set +x 
done
echo "finish."

