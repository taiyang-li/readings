#!/bin/bash
# ʹ��tr 

# �滻
touch log
echo "12345" > log
cat log | tr "0123456789" "1234567890"

# ɾ�� 
echo "hello, 123" >log
cat log | tr  -d "[0-9]"

# ����
echo "hello, 123" > log
cat log | tr -d -c "[0-9\n]"

# ȥ���ظ��ո�
echo "hello,  world" > log
cat log | tr -s " "

