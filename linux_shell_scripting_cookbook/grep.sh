#!/bin/bash
# grep��������ʽ

# grep ��ʾ��ɫ
echo -e "this is a word\nnext line" | grep --color=auto word

# grep -c ͳ��ƥ������
echo -e "1 2 3 4\nhello\n5 6" | grep -c "[0-9]"

# grep -n ��ʾƥ���к�
echo -e "1 2 3 4\nhello\n5 6" | grep -n "[0-9]"

# grep -b ��ʾƥ���ַ�ƫ����
echo -e "gnu is not unix" | grep -b  -o "not"

# grep -l ��ʾƥ����ļ��б�
touch 1.txt
cat>1.txt<<EOF
hello
liyang
EOF

touch 2.txt
cat>2.txt<<EOF
hello
liuyuanyuan
EOF

touch 3.txt
cat>3.txt<<EOF
goodbye
liyang
EOF

grep -l "hello" 1.txt 2.txt 3.txt

# grep -R -n ��λ����
grep "hello" -R -n 1.txt

# grep -i ���Դ�Сд
echo "hello world" | grep -i "HELLO"

# grep -e ƥ������ʽ
echo "this is a line of text" | grep -e "this" -e "line" -o

# grep -f ʹ���ļ��е�ģʽ����ƥ��
touch pattern.txt
cat>pattern.txt<<EOF
hello
world
EOF
grep -f pattern.txt 2.txt

# grep -q  grep��Ĭģʽ
grep -q "hello" 1.txt
if [ $? -ne 0 ]; then 
	echo "hello in 1.txt"
fi

# grep -A -B -C ��ӡƥ����֮ǰ֮���N��
seq 1 10 |  grep 5 -A 3 
seq 1 10 |  grep 5 -B 3
seq 1 10 |  grep 5 -C 3

