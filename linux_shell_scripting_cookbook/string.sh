#!/bin/bash
# ������չ���з��ļ���

file_jpg="sample.jpg"
name=${file_jpg%.*}
filetype=${file_jpg##*.}
echo "name: $name"
echo "filetype: $filetype"

var="hack.fun.book.txt"

# ��������ɾ����һ��ƥ��
echo ${var#*.}
echo ${var##*.}
echo ${var%.*}
echo ${var%%.*}
