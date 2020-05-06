#!/bin/bash

function report_error
{
    echo "error, line: $line, status: $status"
}

function append_line
{
    # set -x 
    local jobname=$1
    local depends=$2
    local right_jobname=""
    local right_depend=""
    for depend in `echo $depends | tr "," " "`; do
        right_jobname=`echo $jobname | tr "." "_"`
        right_depend=`echo $depend | tr "." "_"`
        echo -e "\t$right_depend -> $right_jobname" >> line
    done
    # set +x
}

function append_node
{
    # set -x 
    local jobname=$1
    local comment=$2
    local command=$3
    local right_jobname=`echo $jobname | tr "." "_"`

    echo -e "\t$right_jobname [label = \"jobname = $jobname" >> node
    echo -e "\t\t\tcomment: $comment" >> node
    tmp_command=`echo "$command" | tr -d "\""`

    last_segment=""
    is_even=0
    for segment in $tmp_command; do
        #echo "$segment" | grep -q -e "AUTOOPT_ROOT" -e "WORKROOT"
        #ret=$?
        #if [ $ret -eq 0 ]; then 
        #    segment=`basename $segment`
        #fi
        
        if [ $is_even -eq 1 ]; then 
            echo -e "\t\t\t$last_segment $segment" >> node
        fi
        last_segment=$segment
        ((is_even = 1 - is_even))
    done
    echo -e "\t\t\t\"" >> node

    module=${jobname%%.*}
    color=`grep $module color.conf | grep -v grep | awk '{print $2}'`
    # echo "module: $module, color: $color"
    echo -e "\t\t\tcolor = \"$color\"" >> node
    echo -e "\t\t\tshape = box" >> node
    echo -e "\t\t\t]" >> node
    # set +x
}

# state machine: 
# starting -> start -> jobname -> depends -> comment -> command -> finish 
rm -rf line
rm -rf node
status=starting
while read line; do
    # echo $line

    if [ -z "$line" ]; then
        continue
    fi

    echo "$line" | grep -Pq "(\s+)?#"
    if [ $? -eq 0 ]; then 
        continue
    fi 

    case $status in
        starting | finish)
            echo "$line" | grep -qP "JOB \(" 
            ret=$?
            if [ $ret -eq 0 ]; then 
                status=start
            else
                report_error
            fi
            ;;
        start)
            echo "$line" | grep -qP "\bjobname\s+=\s+"
            ret=$?
            if [ $ret -eq 0 ]; then 
                status=jobname
                jobname=`echo "$line" | grep -oP "\".*\"" | tr -d "\""`
            else
                report_error
            fi
            ;;
        jobname)
            status=depends
            echo "$line" | grep -qP "\bdepends\s+=\s+"
            ret=$?
            if [ $ret -eq 0 ]; then 
                depends=`echo "$line" | grep -oP "\".*\"" | tr -d "\""`
            else
                depends=""
            fi
            ;;
        depends)
            status=comment
            echo "$line" | grep -qP "\bcomment\s+=\s+"
            ret=$?
            if [ $ret -eq 0 ]; then 
                comment=`echo "$line" | grep -oP "\".*\"" | tr -d "\""`
            else
                comment=""
            fi
            ;;
        comment)
            status=command
            echo "$line" | grep -qP "\bcommand\s+=\s+"
            ret=$?
            if [ $ret -eq 0 ]; then 
                command="$line"
            fi
            ;;
        command)
            echo "$line" | grep -qP "^\)$"
            ret=$?
            if [ $ret -eq 0 ]; then 
                status=finish
                # echo "jobname: $jobname, depends: $depends, comment: $comment, command: $command"
                echo "append line for $jobname"
                append_line "$jobname" "$depends"

                echo "append node for $jobname"
                append_node "$jobname" "$comment" "$command"

                echo "module name: ${jobname%%.*}"
            fi
            ;;
    esac
done < ./xxxxx.jobconf

rm -rf xxxxx.dot
echo "digraph example {" >> xxxxx.dot
cat node >> xxxxx.dot
echo "" >> xxxxx.dot
cat line >> xxxxx.dot
echo "}" >> xxxxx.dot

exit 0

