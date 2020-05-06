#!/usr/bin/env python
# -*- coding: utf-8 -*

import sys
filtered_words = set()
with open('./filtered_words.txt') as f:
    for line in f:
        line = line.decode('utf-8').strip()
        filtered_words.add(line)


while True:
    line = sys.stdin.readline()
    if not line:
        break
    
    line = line.decode('utf-8').strip()
    for word in filtered_words:
        line = line.replace(word, len(word) * '*')

    print line.encode('utf-8')
