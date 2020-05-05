#!/bin/bash


seq 1 100 | awk 'NR==50, NR==60'  

touch 1.txt
cat>1.txt<<EOF
line with pattern1
line with pattern2
line with pattern3
line end with pattern4
line with pattern5
EOF

awk '/pattern1/, /end/' 1.txt
