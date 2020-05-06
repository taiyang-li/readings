#!/usr/bin/env python
# coding: utf-8

import xlrd
from lxml import etree

content = []
data = xlrd.open_workbook('input.xls')
table = data.sheets()[0]
for i in range(table.nrows):
    values = table.row_values(i)
    content.append(values)

def list2str(content):
    str = u'\n[\n'
    for value in content:
        str += '\t[%d, %d, %d]\n' % (value[0], value[1], value[2])
    str += ']\n'
    return str

root = etree.Element('root')
students = etree.SubElement(root, 'numbers')
students.append(etree.Comment(u'数字信息'))
students.text = list2str(content)

tree = etree.ElementTree(root)
tree.write('output.xml', pretty_print=True, xml_declaration=True, encoding='utf-8')
