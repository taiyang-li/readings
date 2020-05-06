#!/usr/bin/python 

import sys
import re

line_no = int(sys.stdin.readline().strip())
lines = []
for i in range(line_no):
    lines.append(sys.stdin.readline().strip())
html = '\n'.join(lines)
matches = re.findall(r'<(\w+)[^\n<>]*?>', html, re.M | re.DOTALL)
print ';'.join(sorted(list(set(matches))))

