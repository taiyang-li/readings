#!/bin/bash
# �������д�ӡ����

tput sc 
for i in `seq 1 100000`; do
	echo -n $i
	tput rc
	tput ed
	usleep 10000
done
