#!/bin/bash
command=$1
for instance in `cat ./instance.txt`; do
    echo "------------------$instance-----------------"
    ssh --matrix lijingyi01@${instance} $command
done

