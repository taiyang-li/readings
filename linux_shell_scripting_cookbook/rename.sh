#!/bin/bash
# 1. ����100���ļ�
# 2. ʹ��rename����Щ�ļ�������

types=(jpg png)
for i in `seq 1 100`; do
	prefix=`printf "%03d" $i`
	suffix=${types[$(($RANDOM % 2))]}
	touch "data/$prefix.$suffix"
done

count=1
for img in data/*.jpg  data/*.png; do
	new=`printf "./data/image-%03d.%s" $count ${img##*.}`
	mv $img $new 
	((count++))
done

