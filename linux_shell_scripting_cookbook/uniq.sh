#!/bin/bash
# ʹ��uniq

if [ -e log ]; then 
	rm -f log
fi
touch log
echo "1" >> log
echo "2" >> log 
echo "3" >> log 
echo "4" >> log 
echo "4" >> log 

# ȥ���ظ���
cat log | sort | uniq 

# ��ӡ�ظ�����
cat log | sort | uniq -c 

# ��ӡ�ظ���
cat log | sort | uniq -d 

# ��ӡ���ظ���
cat log | sort | uniq -u

# �����ַ�����
INPUT="KSLDHGLKGHEIGUEFDDIFH"
OUTPUT=`echo $INPUT | sed 's/[^\n]/&\n/g' | sed '/^$/d' | sort | uniq -c | tr -d "\n"`
echo $OUTPUT

