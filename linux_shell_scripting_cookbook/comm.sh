#!/usr/bash
# ��ȡ�����ļ��Ľ�������

touch a.txt
touch b.txt

cat>a.txt<<EOF
apple
orange
gold
silver
steer
iron
EOF

cat>b.txt<<EOF
orange
gold
cookies
carrot
EOF

sort a.txt -o a.txt
sort b.txt -o b.txt

# ����
comm a.txt b.txt | sed 's/^\t\{1,2\}//'

echo "------------------"

# ����
comm a.txt b.txt -1 -2 | sed 's/^\t\{1,2\}//'
