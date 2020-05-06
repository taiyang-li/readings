#!/bin/bash

TIMELIMIT=4
read -p "please input variable: " -t $TIMELIMIT variable <&1
echo 

if [ -z "$variable" ]; then 
	echo "timed out, variable still unset"
else
	echo "variable = $variable"
fi

exit 0
