#!/usr/bin/python 

import sys
import re

cases = int(sys.stdin.readline().strip())
for i in range(cases):
    line = sys.stdin.readline()
    if not line:
        break

    line = line.strip()
    match = re.search(r'^([a-z]{1,3})?[0-9]{2,8}[A-Z]{3,}$', line)
    if match:
        print "VALID"
    else:
        print "INVALID"

