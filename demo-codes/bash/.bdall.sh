#!/bin/bash

function show_usage()
{
	echo "sh $0 <module-name> <version> <comment>" 
	echo "for example: $0 dumper 3.2.1-1 ad集群迁移"
	exit -1
}

if [ $# -lt 3 ]; then 
	show_usage
fi

HOME=/data/liyang/mytools
MODNAME=$1
REVISION=$2
COMMENT=$3
NAME="${MODNAME}-${REVISION}"
WORKSPACE=/data/liyang/*/workspace

if [ ! -d $WORKSPACE/$NAME ]; then 
	echo "error: working folder not found"
	exit -2
fi

echo "START COMMIT SRC..."
cd $WORKSPACE/$NAME
.up-svn.sh 
svn st  | awk -F ' ' '{print $1}' |  grep "M"
if [ $? -eq 0 ]; then 
	.ci-svn.sh "$COMMENT"
fi
# .info-svn.sh > /data/liyang/mytools/src-log.$NAME
svn info $WORKSPACE/$NAME > $HOME/src-log.$NAME
echo "FINISH COMMIT SRC"

echo "START BUILD..."
blade build 
if [ $? -ne 0 ]; then 
	echo "error: blade build faled"
	exit -3
fi
echo "FINISH BUILD"

if [ $MODNAME = "dumper" ]; then 
	RPM="adm_dumper-xuri-${REVISION}.x86_64.rpm"
elif [ $MODNAME = "centre-support" ]; then 
  RPM="adm_centre-supp-${REVISION}.x86_64.rpm"
elif [ $MODNAME = "dumper-support" ]; then 
  RPM="adm_dumper-supp-${REVISION}.x86_64.rpm"
elif [ $MODNAME = "feed-support" ]; then 
  RPM="adm_feed-supp-${REVISION}.x86_64.rpm"
elif [ $MODNAME = "binlog-support" ]; then 
  RPM="adm_binlog-supp-${REVISION}.x86_64.rpm"
elif [ $MODNAME = "centre" ]; then
  RPM="adm_centre-xuri-${REVISION}.x86_64.rpm"
else
	RPM="adm_${NAME}.x86_64.rpm"
fi

if [ -f $WORKSPACE/$NAME/$RPM ]; then 
	rm -rf ./$RPM
fi

echo "START CREATE RPM..."
.crerpm.sh
if [ ! -f $WORKSPACE/$NAME/$RPM ]; then
	echo "error: rpm $RPM not exist"
	exit -4
fi
echo "FINISH CREATE RPM"

if [ $MODNAME = "dumper" ]; then 
	RPMPATH="../rpm/dumper-xuri"
elif [ $MODNAME = "centre-support" ]; then 
  RPMPATH="../rpm/centre-supp"
elif [ $MODNAME = "feed-support" ]; then
  RPMPATH="../rpm/feed-supp"
elif [ $MODNAME = "dumper-support" ]; then 
  RPMPATH="../rpm/dumper-supp"
elif [ $MODNAME = "binlog-support" ]; then
  RPMPATH="../rpm/binlog-supp"
elif [ $MODNAME = "centre" ]; then
  RPMPATH="../rpm/centre-xuri"
else 
	RPMPATH="../rpm/$MODNAME"
fi

if [ ! -d $RPMPATH ]; then 
	echo "error: rpmpath $RPMPATH not exists"
	exit -5
fi

yes | mv $RPM $RPMPATH/
cd $RPMPATH
.up-svn.sh
svn st | grep $REVISION | grep ? 
if [ $? -eq 0 ]; then 
	svn add $RPM 
fi

echo "START COMMIT RPM..."
.ci-svn.sh "$COMMENT"
# .ci-svn.sh "commitagin"
echo "FINISH COMMIT RPM"
.info-svn.sh $RPM > $HOME/rpm-log.$NAME

echo "START GENERATE CHANGELOG..."
LASTREVISION=`.info-svn.sh $RPM | grep 最后修改的版本  | awk -F ': ' '{print $2}'`
RPMURL=`.info-svn.sh $RPM | grep URL  | awk -F ': ' '{print $2}'`
cat > $HOME/$NAME.txt <<EOF
###############################
		$MODNAME
###############################

【发布版本】
版本号：$REVISION
RPM：$RPMURL
RPM revision：$LASTREVISION

【Changelog】

【开者人员】
李扬

EOF

unix2dos $HOME/$NAME.txt
echo "FINISH GENERATE CHANGELOG"

echo "ALL DONE."
