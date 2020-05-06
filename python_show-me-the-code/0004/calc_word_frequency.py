#!/usr/bin/env python
# -*- coding: utf-8 -*

import os
import sys

frequency_by_word = {}
for line in sys.stdin:
    line = line.strip()
    words = line.split()

    for word in words:
        if word in frequency_by_word:
            frequency_by_word[word] += 1
        else:
            frequency_by_word[word] = 1

sorted_frequency_by_word = sorted(frequency_by_word.iteritems(), key=lambda d:d[1], reverse = True)
print type(sorted_frequency_by_word)
for kv in sorted_frequency_by_word:
    print "%s\t%d" % (kv[0], kv[1])
