#!/bin/bash

let "dec = 32"
echo "decimal number = $dec"

let "oct = 032"
echo "octal number = $oct"

let "hex = 0x32"
echo "hexadcimal number = $hex"

echo $((0x9abc))

let "bin=2#1111111111111111"
echo "binary number = $bin"

let "b32 = 32#77"
echo "base-32 number = $b32"

let "b64 = 64#@_"
echo "base-64 number=$b64"

echo 
echo $((36#zz)) $((2#10101010)) $((16#AF16)) $((53#1aA))

exit $?
