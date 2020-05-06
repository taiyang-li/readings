#!/bin/bash

if [ $# -ne 1 ]
then 	
	echo "one argument expected."
	exit 1
fi

if [ -e "$1" ] 
then
	source $1
else
	echo "ebuild file $1 not found"
fi

export ORIGDIR=`pwd`
export WORKDIR=${ORIGDIR}/work
export SRCDIR=${WORKDIR}/${P}

if [ -z "$DISTDIR" ]
then
	DISTDIR=/usr/src/distfiles
fi

export DISTDIR

if [ -d ${WORKDIR} ]
then
	rm -rf ${WORKDIR}
fi

mkdir ${WORKDIR}
tar xzf ${DISTDIR}/${A}
cd ${SRCDIR}
./configure --prefix=/usr
make

