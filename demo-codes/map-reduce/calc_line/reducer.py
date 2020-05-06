#!/bin/env python

import sys

sum = 0
for line in sys.stdin:
	line = int(line.strip())
	sum += line
print sum
