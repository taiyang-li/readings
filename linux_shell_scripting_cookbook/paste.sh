#!/bin/bash
# �����кϲ��ļ�

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

# Ĭ�Ϸָ����ǿո�
paste 1.txt 2.txt

# ָ���ָ���
paste 1.txt 2.txt -d ","

