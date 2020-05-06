#!/usr/bin/python 

import sys
import re

start_with_it = False
end_with_it = False
cases = int(sys.stdin.readline().strip())
for i in range(cases):
    line = sys.stdin.readline()
    if not line:
        break

    line = line.strip()

    match = re.search(r'^hackerrank\b', line)
    start_with_it = (match is not None)

    match = re.search(r'\bhackerrank$', line)
    end_with_it = (match is not None)

    if start_with_it and end_with_it:
        print 0
    elif start_with_it:
        print 1
    elif end_with_it:
        print 2
    else:
        print -1
        

