#!/usr/bin/env python
# coding: utf-8

import xlrd
import re


def str2seconds(in_str):
    tmp = re.split(u'时|分|秒', in_str)
    weight = 1
    seconds = 0
    for i in range(len(tmp)-2, -1, -1):
        seconds += weight * int(tmp[i])
        weight *= 60
    return seconds

content = []
data = xlrd.open_workbook('./2017_12.xls')
table = data.sheets()[0]
values = table.col_values(3)
total_time = 0
for i in range(1, len(values)):
    tmp = str2seconds(values[i])
    total_time += tmp
    # print tmp
print total_time

