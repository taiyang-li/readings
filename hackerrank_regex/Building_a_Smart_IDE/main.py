#!/usr/bin/python 

import sys
import re

lines = sys.stdin.readlines()
text = ''
for line in lines:
    text += line

match_iter = re.finditer(r'(//[^\n]*|/\*.*?\*/)', text, re.M | re.DOTALL)
for match in match_iter:
    comment = match.group(1)
    lines = comment.split('\n')
    for line in lines:
        line = line.strip()
        print line


