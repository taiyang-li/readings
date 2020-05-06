#!/bin/bash

workroot=`cat /path/to/buildfile | grep WORKROOT | awk -F'\x27' '{print $2}'`

find $workroot -type d | grep -v bc_out  | grep -v svn | grep -v git | grep -e "lib2-64" -e "third-64" | grep -P "include$" > pathlist.txt
