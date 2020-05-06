#!/bin/bash


myvar=0
while [  $myvar -ne 10 ]
do 
	echo $myvar
	myvar=$(($myvar+1))
done
