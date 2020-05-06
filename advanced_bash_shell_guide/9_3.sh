#!/bin/bash 

INTERVAL=5

timedout_read()
{
	timeout=$1
	varname=$2
	old_tty_setting=`stty -g`
	stty -icanon min 0 time ${timeout}0
	eval read $varname
	stty "$old_tty_setting"
}

echo 
echo  -n "what is your name! quick! "
timedout_read $INTERVAL your_name

echo 
if [ ! -z "$your_name" ] 
	echo "your name is $your_name"
then 
	echo "timed out"
fi

echo 
exit 0
