#!/usr/bin/env python
# -*- coding: utf-8 -*

import sys
filtered_words = set()
with open('./filtered_words.txt') as f:
    for line in f:
        line = line.strip()
        filtered_words.add(line)


while True:
    line = sys.stdin.readline()
    if not line:
        break

    line = line.strip()
    if line in filtered_words:
        print "Freedom"
    else:
        print "Human Rights"
