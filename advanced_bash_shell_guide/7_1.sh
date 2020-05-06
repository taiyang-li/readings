#!/bin/bash

echo 
echo "testing \"0\""
if [ 0 ]; then 
	echo "0 is true"
else
	echo "0 is false"
fi

echo 
echo "testing \"\1\""
if [ 1 ]; then 
	echo "1 is true"
else
	echo "1 is false"
fi

echo 
echo "testing \"\-1\""
if [ -1 ]; then 
	echo "-1 is true"
else
	echo "-1 is false"
fi

echo 
echo "testing \"NULL\""
if [  ]; then 
	echo "NULL is true"
else
	echo "NULL is false"
fi

echo 
echo "testing \"xyz\""
if [ xyz ]; then 
	echo "random string is true"
else
	echo "random string is false"
fi

echo 
echo "test \"\$xyz\""
if [ $xyz ]; then 
	echo "uninialized variable is true"
else
	echo "uninialized variable is false"
fi

echo 
echo "testing \"-n \$xyz\""
if [ -n "$xyz" ]; then 
	echo "uninitialized variable is true"
else
	echo "uninitialized variable is false"
fi

xyz=
echo 
echo "testing \"-n \$xyz\""
if [ -n "$xyz" ]; then 
	echo "null variable is true"
else
	echo "null variable is false"
fi

echo 
echo "testing \"false\""
if [ "false" ]; then 
	echo "\"false\" is true"
else
	echo "\"false\" is false"
fi

echo 
echo "testing \"\$false\""
if [ "$false" ]; then 
	echo "\"\$false\" is true"
else
	echo "\"\$false\" is false"
fi

echo 
exit 0
