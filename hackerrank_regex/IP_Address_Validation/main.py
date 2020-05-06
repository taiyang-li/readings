#!/usr/bin/python 

import sys
import re

NEITHER = "Neither"
IPV4 = "IPv4"
IPV6 = "IPv6"
wrong_format = False
cases = int(sys.stdin.readline().strip())

for i in range(cases):
    line = sys.stdin.readline()
    if not line:
        break

    line = line.strip()
    wrong_format = False

    match = re.search(r'^(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3})$', line)
    if match:
        for j in range(4):
            value = int(match.group(j+1))
            if value < 0 or value > 255:
                wrong_format = True
                break

        if wrong_format:
            print NEITHER
        else:
            print IPV4

        continue

    match = re.search(r'^([a-fA-F0-9]{1,4}:){7}[a-fA-F0-9]{1,4}$', line)
    if match:
        print IPV6
        continue

    print NEITHER


