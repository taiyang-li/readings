#!/usr/bin/env python
# coding: utf-8

import xlrd
from lxml import etree


content = {}
data = xlrd.open_workbook('input.xls')
table = data.sheets()[0]
for i in range(table.nrows):
    values = table.row_values(i)
    content[values[0]] = values[1]

def dict2str(d):
    str = u'\n{\n'
    for k, v in d.items():
        str += '\t"%s": "%s"\n' % (k, v)
    str += '}\n'
    return str

root = etree.Element('root')
students = etree.SubElement(root, 'cities')
students.append(etree.Comment(u'城市信息'))
students.text = dict2str(content)

tree = etree.ElementTree(root)
tree.write('output.xml', pretty_print=True, xml_declaration=True, encoding='utf-8')

