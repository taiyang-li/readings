#!/bin/bash

LOG_DIR=/var/log
ROOT_UID=0
LINES=50
E_XCD=86
E_NOTROOT=87

if [ $UID -ne $ROOT_UID ]; then 
	echo "must be root to run this script"
	exit "$E_NOTROOT"
fi

if [ -n $1 ]; then 
	lines=$1
else
	lines=$LINES
fi

cd $LOG_DIR
if [ `pwd` != $LOG_DIR ]; then 
	echo "can't change to $LOG_DIR"
	exit $E_XCD
fi

# messages ±£Áô $linesÐÐ
echo "lines: $lines"
tail -n $lines  messages > mesg.tmp
mv mesg.tmp messages

cat /dev/null > wtmp
echo "log files cleaned up"
exit 0
