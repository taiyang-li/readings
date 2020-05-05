#!/usr/bash
# 查找并删除重复文件
ls -Sl ./data/ | awk 'BEGIN{
	getline;
	getline;
	name1 = $8;
	size = $5;
}
{
	name2 = $8;
	if (size == $5)
	{
		"md5sum " name1 | getline;
		csum1 = $1;
		"md5sum " name2 | getline;
		csum2 = $2;
		if (csum1 == csum2)
		{
			print name1;
			print name2;
		}
	}
	name1 = name2;
	size = $5;
}'   | sort -u > duplicate_files

cat dubplicate_files | xargs -l {} md5sum {} | sort | uniq -w 32 | awk '{print $2}' | sort -u > duplicate_sample

comm duplicate_files duplicate_sample -2 -3 | tee /dev/stderr | xargs -l {} rm -rf {}
