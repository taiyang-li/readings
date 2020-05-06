#!/bin/bash

while True; do
    hour=`date +'%H'`
    if [ $hour -eq 12 ]; then 
        rm -rf ../conf/checkpoint.txt
        python fetcher.py
        python diff_report_generator.py
        python save_newhouse.py
    fi
    sleep 3600
done
