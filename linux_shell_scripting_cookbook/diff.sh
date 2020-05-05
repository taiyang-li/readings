#!/bin/bash
# 生成文件统计信息

touch 1.txt
touch 2.txt

cat>1.txt<<EOF
1
2
3
4
EOF

cat>2.txt<<EOF
1
3
4
EOF

diff -u 1.txt 2.txt > 12.patch
patch -p1 1.txt < 12.patch
