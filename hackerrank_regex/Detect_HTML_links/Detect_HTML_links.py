#!/usr/bin/python 

import sys
import re

cases = int(sys.stdin.readline().strip())
for i in range(cases):
    line = sys.stdin.readline()
    if not line:
        break

    line = line.strip()

    match_iter = re.finditer(r'<a href="(.*?)"[^><]*>(<[^<>]+>)*?([^<>]+)?(<[^<>]+>)*?</a>', line)
    if not match_iter:
        continue
    
    for match in match_iter:
        link = match.group(1)
        name = match.group(3)
        if name is not None:
            print "%s,%s" % (link, name.strip())
        else:
            print "%s," % (link)


