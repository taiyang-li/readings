#!/bin/bash

if [ $# -ne 2 ]
	echo "please specify two args"
	exit 1
fi


if [ -z "$DISTDIR" ]
then 
	DISTDIR=/usr/src/distfiles
fi

export DISTDIR

ebuild_unpack()
{
	cd ${ORIGDIR}
	if [ -d "$WORKDIR" ]
	then
		rm -f $WORKDIR
	fi
	mkdir $WORKDIR
	cd $WORKDIR
	if [ ! -e ${DISTDIR}/${A} ]
	then 
		echo "${DISTDIR}/${A} does not exist"
		exit 1
	fi
	tar xzf ${DISTDIR}/${A}
	echo "unpacked  ${DISTDIR}/${A}"
}


ebuild_compile()
{
	cd ${SRCDIR}
	if [ ! -d "${SRCDIR}" ]
	then
		echo "${SRCDIR} does not exist"
		exit 1
	fi
	./configure --prefix=/usr
	make
	
}

export ORIGDIR=`pwd`
export WORKDIR=${ORIGDIR}/work

if [ -e  "$1" ]
then 
	source $1
else
	echo "ebuild file $1 not found"
	exit 1
fi

export SRCDIR=${WORKDIR}/${P}
case "${2}" in
	unpack)
		ebuild_unpack
		;;
	compile)
		ebuild_compile
		;;
	all)
		ebuild_unpack
		ebuild_compile
		;;
	*)
		echo "please  specify unpack, compile"
		exit 1
esac
