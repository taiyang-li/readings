#!/bin/bash
# 计算程序执行时间


btime=`date +%s`
sleep 2
etime=`date +%s`
diff=$((etime-btime))
echo "task time : $diff seconds"
