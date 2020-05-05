#!/bin/bash
# 根据扩展名切分文件名

file_jpg="sample.jpg"
name=${file_jpg%.*}
filetype=${file_jpg##*.}
echo "name: $name"
echo "filetype: $filetype"

var="hack.fun.book.txt"

# 从左至右删除第一个匹配
echo ${var#*.}
echo ${var##*.}
echo ${var%.*}
echo ${var%%.*}
