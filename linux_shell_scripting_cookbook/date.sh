#!/bin/bash
# �������ִ��ʱ��


btime=`date +%s`
sleep 2
etime=`date +%s`
diff=$((etime-btime))
echo "task time : $diff seconds"
