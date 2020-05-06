#!/bin/bash

function show_usage()
{
    echo "./$0 <userid> <planid>"
    exit -1
}

if [ $# -lt 2 ]; then 
    show_usage
fi

userid=$1
planid=$2
this_path=$(dirname $(readlink -f $0))

sh $this_path/preprocess.sh $userid $planid
if [ $? -ne 0 ]; then 
    echo "preprocess failed, exit now"
    exit -1
fi

python $this_path/data2sql.py $userid $planid
if [ $? -ne 0 ]; then 
    echo "data2sql failed, exit now"
    exit -1
fi

python $this_path/exec_sql.py $userid $planid
if [ $? -ne 0 ]; then 
    echo "exec_sql failed, exit now"
    exit -1
fi

sh $this_path/check.sh $userid $planid
if [ $? -ne 0 ]; then 
    echo "check failed, exit now"
    exit -1
fi

exit 0
