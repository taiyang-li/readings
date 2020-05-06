#!/usr/bin/env python
# -*- coding: utf-8 -*

from collections import Counter
import re
import os

# 过滤词
stop_words = ['the', 'in', 'of', 'and', 'to', 'has', 'that', 's', 'is', 'are', 'a', 'with', 'as', 'an', 'for', 'on']

def get_counter(filepath):
    pattern = r'''[a-zA-Z]+|\$?\d+%?$'''
    with open(filepath) as f:
        matches = re.findall(pattern, f.read())
        return Counter(matches)


def run(filedir):
    result = Counter()
    for name in os.listdir(filedir):
        filepath = "%s/%s" % (filedir, name)
        ext = os.path.splitext(name)[1]
        if ext == ".txt":
            result += get_counter(filepath)
    
    for word in stop_words:
        result[word] = 0
    
    return result.most_common(1)[0][0]

print run('./data_in')

