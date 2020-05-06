#!/bin/bash

set -- "First code" "second" "thrid:one" "" "fifth: :one"

echo 
c=0
echo "IFS unchanged, using \"\$*\""
for i in "$*"
do 
	echo "$((c+=1)): [$i]"
done
echo ---

echo "IFS unchanged, using \$*"
c=0
for i in $*
do
	echo "$((c+=1)): [$i]"
done
echo ---

echo "IFS unchanged, using \"\$@\""
c=0
for i in "$@"
do
	echo "$((c+=1)): [$i]"
done
echo ---

echo "IFS unchanged, using \$@"
c=0
for i in $@
do
	echo "$((c+=1)): [$i]"
done
echo ---

IFS=:
echo "IFS=:, using \"\$*\""
c=0
for i in "$*"
do 
	echo "$((c+=1)): [$i]"
done
echo ---

echo "IFS:, using \$*"
c=0
for i in $*
do
	echo "$((c+=1)): [$i]"
done
echo ---

var=$*
echo "IFS=:, using \"\$var\""
c=0
for i in "$var"
do	
	echo "$((c+=1)): [$i]"
done
echo ---

echo "IFS=:, using \$var"
c=0
for i in $var
do 
	echo "$((c+=1)): [$i]"
done
echo ---

var="$*"
echo "IFS=:, using \$var"
c=0
for i in $var
do
	echo "$((c+=1)): [$i]"
done
echo ---

echo "IFS=:, using \"\$var\""
c=0
for i in "$var"
do
	echo "$((c+=1)): [$i]"
done
echo ---


