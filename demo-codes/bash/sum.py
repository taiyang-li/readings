#!/usr/bin/env python
# coding: utf-8

import sys

sum = 0.0
for line in sys.stdin:
    line = line.strip('\n')
    value = float(line)
    sum += value
print sum

