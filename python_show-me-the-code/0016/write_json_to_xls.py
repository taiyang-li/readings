#!/usr/bin/env python
# coding: utf-8

import json
import xlwt
import xlrd

with open('./input.txt') as f:
    data = json.load(f)
    print data

book = xlwt.Workbook()
table = book.add_sheet('student')

r = 0
for item in data:
    c = 0
    for value in item:
        table.write(r, c, value)
        c += 1
    r += 1

book.save('output.xls')
