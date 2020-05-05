#!/bin/bash
# 按照列合并文件

touch 1.txt
cat>1.txt<<EOF
1
2
3
4
5
EOF

touch 2.txt
cat>2.txt<<EOF
a
b
c
d
e
f
EOF

# 默认分隔符是空格
paste 1.txt 2.txt

# 指定分隔符
paste 1.txt 2.txt -d ","

