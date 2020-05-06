#!/bin/bash

year_month_day=`date +%Y-%m-%d`
hour_min_sec=`date +%H%M%S`
if [ -e "./log" ]; then 
	rm -rf ./log
fi

echo "current date: $year_month_day" >> log 
echo "current time: $hour_min_sec" >> log 
echo "all the users\n `who`" >> log 
echo "uptime: `uptime`" >> log 
