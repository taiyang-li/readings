#!/usr/bin/env python
# coding: utf-8

import json
import xlwt
import xlrd

with open('./input.txt') as f:
    data = json.load(f)

book = xlwt.Workbook()
table = book.add_sheet('student')

r = 0
for i in data:
    table.write(r, 0, i.encode('utf-8'))

    values = data[i]
    c = 1
    for v in values:
        if isinstance(v, str):
            table.write(r, c, v.encode('utf-8')) 
        else:
            table.write(r, c, v)
        c += 1
    r += 1

book.save('output.xls')
