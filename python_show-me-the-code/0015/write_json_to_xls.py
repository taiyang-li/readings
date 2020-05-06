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
for i in data:
    table.write(r, 0, i)
    city = data[i]
    table.write(r, 1, city)
    r += 1

book.save('output.xls')
