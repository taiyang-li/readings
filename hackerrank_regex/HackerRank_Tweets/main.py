#!/usr/bin/python 

import sys
import re

cases = int(sys.stdin.readline().strip())
cnt = 0
for i in range(cases):
    line = sys.stdin.readline()
    if not line:
        break

    line = line.strip()
    match = re.search(r'\b[#@]?HackerRank\b', line, re.I)
    if match is not None:
        cnt += 1

print cnt
