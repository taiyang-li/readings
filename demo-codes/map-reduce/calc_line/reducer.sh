#!/bin/bash

sum=0
while read i; do
	((sum += i))
done
echo $sum
