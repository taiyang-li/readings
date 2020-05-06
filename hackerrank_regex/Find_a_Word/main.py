#!/usr/bin/python 

import sys
import re

lines = []
words = []

line_no = int(sys.stdin.readline().strip())
for i in range(line_no):
    line = sys.stdin.readline().strip()
    lines.append(line)

word_no = int(sys.stdin.readline().strip())
for i in range(word_no):
    word = sys.stdin.readline().strip()
    words.append(word)

# construct regular expression
pattern = r'\b(' + '|'.join(words) + r')\b'
cnt_by_word = {}
for line in lines:
    matches = re.findall(pattern, line)
    for match in matches:
        if not match in cnt_by_word:
            cnt_by_word[match] = 1
        else:
            cnt_by_word[match] += 1

for word in words:
    if not word in cnt_by_word:
        print 0
    else:
        print cnt_by_word[word]
