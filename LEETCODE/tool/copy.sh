#!/bin/bash

for file in `cat ./files.txt`; do
    cp /Volumes/work/test/$file ./
done
