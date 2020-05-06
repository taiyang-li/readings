#!/bin/bash

LOG_DIR=/var/log
cd $LOG_DIR	
cat /dev/null > messges
cat /dev/null > wtmp
echo "log files cleaned up"
exit
