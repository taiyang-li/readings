#!/usr/bin/python 
import sys
import re

VALID = "YES"
INVALID = "NO"
cases = int(sys.stdin.readline().strip())
for i in range(cases):
    line = sys.stdin.readline()
    if not line:
        break

    line = line.strip()
    match = re.search(r'^[A-Z]{5}\d{4}[A-Z]$', line)
    if match:
        print VALID
    else:
        print INVALID
