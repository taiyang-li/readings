#!/bin/bash
# ʹ��sort

if [ -e data.txt ]; then 
	rm -f data.txt
fi
touch data.txt
echo "1 max 2000" >> data.txt
echo "2 winxp 4000" >> data.txt
echo "3 bsd 1000" >> data.txt
echo "4 linux 1000" >> data.txt

# �����ַ�������
cat data.txt | sort 

# ��������������ļ�
cat data.txt | sort -o log

# ������������
cat data.txt | sort -n

# ���յڶ��н�������
cat data.txt | sort -k 2

# ���յ�һ�н�����������
cat data.txt | sort -nk 1


