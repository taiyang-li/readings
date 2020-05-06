#!/bin/bash

path=`readlink -f $1`
host=`hostname`
echo "work@$host:$path"
