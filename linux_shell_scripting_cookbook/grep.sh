#!/bin/bash
# grep和正则表达式

# grep 显示颜色
echo -e "this is a word\nnext line" | grep --color=auto word

# grep -c 统计匹配行数
echo -e "1 2 3 4\nhello\n5 6" | grep -c "[0-9]"

# grep -n 显示匹配行号
echo -e "1 2 3 4\nhello\n5 6" | grep -n "[0-9]"

# grep -b 显示匹配字符偏移量
echo -e "gnu is not unix" | grep -b  -o "not"

# grep -l 显示匹配的文件列表
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

# grep -R -n 定位代码
grep "hello" -R -n 1.txt

# grep -i 忽略大小写
echo "hello world" | grep -i "HELLO"

# grep -e 匹配多个样式
echo "this is a line of text" | grep -e "this" -e "line" -o

# grep -f 使用文件中的模式进行匹配
touch pattern.txt
cat>pattern.txt<<EOF
hello
world
EOF
grep -f pattern.txt 2.txt

# grep -q  grep静默模式
grep -q "hello" 1.txt
if [ $? -ne 0 ]; then 
	echo "hello in 1.txt"
fi

# grep -A -B -C 打印匹配行之前之后的N行
seq 1 10 |  grep 5 -A 3 
seq 1 10 |  grep 5 -B 3
seq 1 10 |  grep 5 -C 3

