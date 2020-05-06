#!/bin/bash

echo ""

echo "this will print 
as two lines"

echo "this will print \
as one line"

echo "\v\v\v\v"
echo "============"
echo "VERTICAL TABS"
echo -e "\v\v\v\v"
echo "============"

echo
echo "NEWLINE AND (maybe) BEEP"
echo $'\n'
echo $'\a'

echo "instroducing the \$\' ... \' string-expansion construct ..."
echo "... featuring more quotation marks"

echo $'\t \042 \t'
echo $'\t \x22 \t'
echo 

triple_underline=$'\137\137\137'
echo "$triple_underline UNSERLINE $triple_underline"
echo 
ABC=$'\101\102\103\010'
echo $ABC
echo 

escape=$'\033'
echo "\"escapes\" echoes as $escape"
echo 
exit 0
