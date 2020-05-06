#!/bin/bash

ROOT_UID=0
if [ "$UID" -eq "$ROOT_UID" ]; then 
	echo "your are root"
else
	echo "your are not root"
fi

ROOTUSER_NAME=root
username=`id -nu`
if [ "$username" = "$ROOTUSER_NAME" ]; then 
	echo "your are root"
else
	echo "your are not root"
fi

exit 0
