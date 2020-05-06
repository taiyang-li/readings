#!/usr/bin/python 

import sys
import re

cases = int(sys.stdin.readline().strip())
html = ''
lines = sys.stdin.readlines()
for line in lines:
    html += line

attrs_by_tag = {}
groups = re.findall(r'<(\w+)(\s+\w+\s*=\s*["\'][^<>]*["\'])*?\s*/?>', html, re.M | re.DOTALL)
# print groups
for group in groups:
    tag = group[0]
    buf = group[1]
    if tag not in attrs_by_tag:
        attrs_by_tag[tag] = set()

    if len(buf.strip()) == 0:
        attrs_by_tag[tag].add('')
        continue

    attrs = re.findall(r'\s+(\w+)\s*=', buf, re.M | re.DOTALL)
    for attr in attrs:
        attrs_by_tag[tag].add(attr)

    """
    tag = match.group(1)
    attr = '' if match.group(3) is None else match.group(3)
    if tag not in attrs_by_tag:
        attrs_by_tag[tag] = set()
    attrs_by_tag[tag].add(attr)
    """

for attr in sorted(attrs_by_tag.keys()):
    print "%s:%s" % (attr, ','.join(sorted(list(attrs_by_tag[attr]))))
