#!/bin/bash

# TODO show log
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

input_dir=$this_path/../data/db_export
output_dir=$this_path/../data/data.$userid.$planid
if [ ! -d $input_dir ]; then 
    echo "$input_dir not exists, exit now"
    exit -1
fi

if [ -d $output_dir ]; then 
    rm -rf $output_dir
fi
mkdir $output_dir

for name in `ls $input_dir`; do
    path=$input_dir/$name

    if [ ! -d $path ]; then 
        continue
    fi 

    if [ "$name" == "user" ]; then 
        cat $path/part* | awk -F'\t' -v userid=$userid '{if ($1 == userid) print $0}' | sort | uniq > $output_dir/$name
    else
        cat $path/part* | awk -F'\t' -v userid=$userid -v planid=$planid '{if ($1 == userid && $2 == planid) print $0}' | sort | uniq > $output_dir/$name
    fi
done

input_dir=$this_path/../data/db_data
if [ ! -d $input_dir ]; then 
    echo "$input_dir not exist, exit now"
    exit -1
fi

src_names=("status_exist.dat" "adcore_exist.dat" "maintain_db.dat")
dst_names=("status" "adcore" "maintain")
for ((i=0; i<${#src_names[@]}; ++i)); do
    src_name=${src_names[$i]}
    dst_name=${dst_names[$i]}
    path=$input_dir/$src_name

    if [ ! -f $path ]; then 
        echo "path $path not exists, exit now"
        exit -1
    fi

    cat $path | grep "\b$userid\b" | grep "\b$planid\b" | sort | uniq > $output_dir/$dst_name
done

# preprocess ao db data
input_file=$this_path/../data/das_incre_data_file.unsort
if [ ! -f $input_file ]; then 
    echo "$input_file not exists, exit now"
    exit -1
fi
dst_name='das'
cat $input_file | grep "\b$userid\b" | grep "\b$planid\b" | sort | uniq > $output_dir/$dst_name

echo "preprocess done"
exit 0
