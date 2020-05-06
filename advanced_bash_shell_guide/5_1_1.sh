#!/bin/bash

IFS='\'
var2="\\\\\""
echo $var2
echo "$var2"
echo 

var3='\\\\'
echo $var3
echo "$var3"
echo 

echo "$(echo '"')"
var1="two bits"
echo "\$var1="$var1""

if [[  "$(du "$My_File1")" -gt "$(du "$My_File2")" ]];
then 
fi
