#!/usr/bin/python 

import sys
import re

cases = int(sys.stdin.readline().strip())
emails = set()
for i in range(cases):
    line = sys.stdin.readline()
    if not line:
        break

    line = line.strip()
    match_iter = re.finditer(r'\b(\w+(\.\w+)*@\w+(\.\w+)*)\b', line)
    for match in match_iter:
        emails.add(match.group(1))

print ';'.join(sorted(list(emails)))


