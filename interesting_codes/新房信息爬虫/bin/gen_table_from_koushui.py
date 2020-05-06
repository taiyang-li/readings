#!/usr/bin/env python 
# coding: utf-8

import sys
import re
import csv
import pprint

input_filename = sys.argv[1];
update_time = ''
fanginfo = []  
header = [u'楼盘', u'截止日期', u'所在区域', u'登记时间', u'开房房源', u'优先比例', u'开盘均价', u'购买条件', u'主力户型', u'登记情况', u'中签率']

with open('../data/%s' % (input_filename)) as f:
    deadline_patten = re.compile(u'^(.*)[（\(]截止(.*)[）\)]')
    detail_pattern = re.compile(u'^(.*)：(.*)$')
    for line in f:
        line = line.strip().decode('utf-8')
        if len(line) == 0:
            continue

        # 楼盘名称
        if line.find(u'：') == -1:
            fanginfo.append({})
            match = deadline_patten.search(line)
            if match:
                fanginfo[-1][u'楼盘'] = match.group(1)
                fanginfo[-1][u'截止日期'] = match.group(2)
            else:
                print line
        else:
            match = detail_pattern.search(line)
            if match:
                key = match.group(1)
                value = match.group(2)
                fanginfo[-1][key] = value
            else:
                print "---", line 

with open('../data/%s.csv' % (input_filename.split('.')[0]), 'wb') as csvfile:
    writer = csv.writer(csvfile, dialect='excel')
    # writer.writerow([name.decode('utf-8').encode('gbk') for name in header])
    writer.writerow([name.encode('gbk') for name in header])
    # writer.writerow(header)
    for item in fanginfo:
        row = []
        for name in header:
            if name in item:
                # print item[name]
                # row.append(item[name].decode('utf-8').encode('gbk'))
                row.append(item[name].encode('gbk'))
                # row.append(item[name].decode('utf-8'))
            else:
                row.append('-')
        writer.writerow(row)

