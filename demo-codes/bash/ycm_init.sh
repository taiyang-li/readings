#!/bin/bash

function show_usage()
{
    echo "Usage: ycm_init ./ without_find"
    exit -1
}

if [ $# -lt 2 ]; then 
    show_usage
fi

path=$1
mode=$2
srcpath=~/.vim/bundle/YouCompleteMe/third_party/ycmd/cpp/ycm/.ycm_extra_conf.py
yes | cp $srcpath ./

if [ "$mode" = "with_find" ]; then 
    files=$(find $path -type d -iname "[^.]*" -maxdepth 5 ! -path "*.svn*" ! -path "*.git*" 2>/dev/null)
elif [ "$mode" = "without_find" ]; then
    files=`cat filelist.txt`
else
    echo "invalid mode $mode"
    exit -1
fi

for path in $files; do
    echo $path
    sed -i ".bak" "/Wall/a\ 
        \'-isystem\', \'$path\',\ 
        " .ycm_extra_conf.py
done
