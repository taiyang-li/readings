#!/bin/bash
# ʹ��tput�����ն�

while true; do
	for ch in '-' '=' '|'; do 
		tput cup 33 0
		echo -n $ch
		sleep 1
	done
done
