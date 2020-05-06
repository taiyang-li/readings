#!/usr/bin/python 

import sys
import re

cases = int(sys.stdin.readline().strip())
for i in range(cases):
    line = sys.stdin.readline()
    if not line:
        break

    line = line.strip()
    match = re.search(r'(\d{1,3})([ \-])(\d{1,3})\2(\d{4,10})', line)
    if match:
        print "CountryCode=%s,LocalAreaCode=%s,Number=%s" % (match.group(1), match.group(3), match.group(4))

