#!/usr/bin/python 

import sys
import re

VALID = "Valid"
INVALID = "Invalid"
cases = int(sys.stdin.readline().strip())
for i in range(cases):
    line = sys.stdin.readline()
    if not line:
        break

    line = line.strip()
    search_obj = re.search(r'\(([\+\-]?\d+(\.\d+)?), ([\+\-]?\d+(\.\d+)?)\)', line)
    if not search_obj:
        print INVALID
        continue

    search_obj1= re.search(r'[\+\-\( ]0\d+\.?', line)
    if search_obj1:
        print INVALID
        continue
    
    latitude = float(search_obj.group(1))
    longitude = float(search_obj.group(3))
    if latitude > 90.0 or latitude < -90.0 or longitude > 180.0 or longitude < -180.0:
        print INVALID
        continue

    print VALID

