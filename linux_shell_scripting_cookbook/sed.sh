#!/bin/bash
# sed�����÷�

# sed "s///" �滻
echo  "hello wolrd" | sed "s/hello/goodbye/"
touch 1.txt
cat>1.txt<<EOF
hello world
EOF

# sed -i �滻�ļ�����
sed -i 's/hello/goodbye/' 1.txt

# sed 's///g' �滻����ƥ������
echo "thisthisthisthis" | sed 's/this/THIS/g'

# sed 's///ng' �ӵ�n��ƥ�俪ʼ�滻
echo "thisthisthisthis" | sed 's/this/THIS/2g'

# sed '//d' ɾ��ƥ����
cat diff.sh | sed '/^$/d' 

# ƥ���ַ������
echo this is an example | sed 's/\w\+/[&]/g'

# ��׽�ַ���
echo "this is a digit 7 in a numbger" | sed 's/digit \([0-9]\)/\1/'
