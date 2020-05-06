#!/bin/bash

E_BADARGS=85

if [ ! -n "$1" ]; then 
	echo "usage: `basename $0` argument1 argument2 etc"
	exit $E_BADARGS
fi

index=1

echo "listting args with \"\$*\":"
for arg in "$*"
do
	echo "arg #$index = $arg"
	let "index+=1"
done
echo "entire arg list seen as a single word"

echo 
index=1
for arg in "$@"
do 
	echo "arg #$index = $arg"
	let "index+=1"
done
echo "arg list seen as a separate words"

echo 
index=1
echo "listing args with \$* (unquoted):"
for arg in $*
do
	echo "arg #$index = $arg"
	let "index+=1"
done
echo "arg list seen as separate words"

exit 0
