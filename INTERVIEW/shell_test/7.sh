#!/bin/bash


if [ -d work ]
then 
	rm -rf work
fi

mkdir work
cd work
tar xzf /usr/src/distfiles/sed-3.02.tar.gz
cd sed-3.02
./configure --prefix=/usr
make

