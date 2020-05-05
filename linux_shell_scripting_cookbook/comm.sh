#!/usr/bash
# 求取两个文件的交集并集

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

# 并集
comm a.txt b.txt | sed 's/^\t\{1,2\}//'

echo "------------------"

# 交集
comm a.txt b.txt -1 -2 | sed 's/^\t\{1,2\}//'
