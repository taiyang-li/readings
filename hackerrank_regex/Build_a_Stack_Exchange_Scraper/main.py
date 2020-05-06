#!/usr/bin/python 

import sys
import re

# cases = int(sys.stdin.readline().strip())
lines = sys.stdin.readlines()
html = ''
for line in lines:
    html += line

groups = re.findall(r'(<h3>[^\n]*?</h3>).*?(asked <span [^<>\n]*>[^<>\n]*</span>)', html, re.M | re.DOTALL)
# groups = re.findall(r'(<h3>[^\n]*?</h3>)', html, re.M | re.DOTALL)
# groups = re.findall(r'(asked <span [^<>\n]*>[^<>\n]*</span>)', html, re.M | re.DOTALL)

for group in groups:
    h3_body = group[0]
    span_body = group[1]

    id_title = re.findall(r'/(\d+)/[^<>]*>([^<>]+)<', h3_body)
    time = re.findall(r'>([^<>]+)<', span_body)
    
    # print group, id_title, time

    id = id_title[0][0]
    title = id_title[0][1]
    time = time[0]
    print "%s;%s;%s" % (id, title, time)
