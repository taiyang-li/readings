#!/usr/bin/python 

import sys
import re

cases = int(sys.stdin.readline().strip())
for i in range(cases):
    line = sys.stdin.readline()
    if not line:
        break

    line = line.strip()
    match = re.search(r'^[Hh][Ii]\s[a-ce-zA-CE-Z]', line)
    if match:
        print line

