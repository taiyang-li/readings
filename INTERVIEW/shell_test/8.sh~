#!/bib/bash

P="sed-3.02"

A=${P}.tar.gz

export ORIGDIR=`pwd`
export WORKDIR=$ORIGDIR}/work
export SRCDIR=${WORKDIR}/${P}


if [ -z "$DISTDIR" ]
then 	
	DISTDIR=/usr/src/distfiles
fi

if [ -d  "$WORKDIR" ]
then
	rm -rf ${WORKDIR}
fi

mkdir ${WORKDIR}
cd ${WORKDIR}
tar xzf ${DISTDIR}/${A}
cd ${SRCDIR}
./configure --prefix=/usr
make

