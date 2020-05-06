#!/bin/bash

path=`readlink -f $1`
host=`hostname`
echo "ftp://$host$path"
