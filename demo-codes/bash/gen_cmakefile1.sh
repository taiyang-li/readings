#!/bin/bash

function show_usage()
{
    echo "$0 <topdir>"
    exit -1
}

if [ $# -lt 1 ]; then 
    show_usage
fi
topdir=$1

# find include paths
incs=`find $topdir -name "*.hpp" -or -name "*.h" -exec dirname {} \; | sort | uniq`
all_incs=""
for inc in $incs; do
    echo $inc | grep -q "\binclude\b"
    if [ $? -eq 0 ]; then 
        name=`basename $inc`
        while [ "$name" != "include" -a "$name" != "." ]; do
            inc=`dirname $inc`
            name=`basename $inc`
        done
        if [ "$name" = "include" ]; then 
            all_incs="$all_incs $inc"
        fi
    else
        name=`basename $inc`
        while [ "$name" != "." ]; do
            all_incs="$all_incs $inc"
            inc=`dirname $inc`
            name=`basename $inc`
        done
    fi
done

for inc in $incs; do
    all_incs="$all_incs $inc"
done
all_uniq_incs=`echo "$all_incs" | tr " " "\n" | grep -v "^$" | sort | uniq`
# echo $all_uniq_incs
# all_uniq_incs="$incs"

# find src files
srcs=`find $topdir -name "*.cpp" -or -name "*.cc" -or -name "*.c" -or -name "*.tcc"`

cmakefile=$topdir/CMakeLists1.txt
cat > $cmakefile <<EOF
cmake_minimum_required(VERSION 3.5)
project(report_engine)
set(CMAKE_CXX_FLAGS "\${CMAKE_CXX_FLAGS} -std=c++11")
EOF

echo "set(SOURCE_FILES" >> $cmakefile
for src in $srcs; do
    echo -e "\t$src" >> $cmakefile
done
echo ")" >> $cmakefile

echo "include_directories(" >> $cmakefile
for inc in $all_uniq_incs; do
    echo -e "\t$inc" >> $cmakefile
done
echo -e "\t." >> $cmakefile
echo ")" >> $cmakefile

cat >> $cmakefile <<EOF
add_executable(myprogram \${SOURCE_FILES})
EOF


