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
data_dir=$this_path/../data/data.$userid.$planid
count_dir=$this_path/../data/count.$userid.$planid

if [ ! -d $data_dir -o ! -d $count_dir ]; then 
    echo "$data_dir or $count_dir not exists, exit now"
    exit -1
fi

for name in `ls $data_dir`; do
    data_path=$data_dir/$name
    count_path=$count_dir/$name.count

    if [ ! -f $count_path ]; then 
        echo "$count_path not exists, skip"
        continue
    fi

    data_count=`wc -l $data_path | awk '{print $1}'`
    db_counts=`cat $count_path | awk -F'\t' '{print $2}' | tr "\n" " "`
    for db_count in $db_counts; do
        if [ $data_count -eq $db_count ]; then 
            echo "check $name success, data_count: $data_count, db_count: $db_count"
        else
            echo "check $name failed, data_count: $data_count, db_count: $db_count"
        fi
    done
done

echo "check done"
exit 0
