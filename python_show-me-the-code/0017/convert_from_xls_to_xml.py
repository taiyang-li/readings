#!/usr/bin/env python
# coding: utf-8

import xlrd
from lxml import etree


content = {}
data = xlrd.open_workbook('input.xls')
table = data.sheets()[0]
for i in range(table.nrows):
    values = table.row_values(i)
    content[values[0]] = values[1:]

def dict2str(d):
    str = u''
    str += '\n{\n'
    for k, v in d.items():
        str += u'\t"%s": ["%s", %d, %d, %d]\n' % (k, v[0], v[1], v[2], v[3])
    str += '}\n'
    return str


root = etree.Element('root')
students = etree.SubElement(root, 'students')
students.append(etree.Comment(u'学生信息表 "id" : [名字, 数学, 语文, 英文]'))
students.text = dict2str(content)

tree = etree.ElementTree(root)
tree.write('output.xml', pretty_print=True, xml_declaration=True, encoding='utf-8')


