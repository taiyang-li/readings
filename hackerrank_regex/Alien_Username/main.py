#!/usr/bin/python 

import sys
import re

VALID = "VALID"
INVALID = "INVALID"
cases = int(sys.stdin.readline().strip())
for i in range(cases):
    line = sys.stdin.readline()
    if not line:
        break

    line = line.strip()
    match = re.search(r'^[\._]\d+[a-zA-Z]*_?$', line)
    if match:
        print VALID
    else:
        print INVALID

