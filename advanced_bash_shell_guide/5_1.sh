#!/bin/bash


echo 
var="']\\{}\$\""
echo $var
echo "$var"

echo 
IFS='\'
echo $var
echo "$var"

IFS=' '
var='hello world'
for i in $var; do 
	echo $i
done 
for i in "$var"; do 
	echo $i
done
