#!/bin/bash 

for file in `cat ./files.txt`; do
    diff -abru ../$file ./$file > $file.diff
done
