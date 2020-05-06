#!/usr/bin/python 

import sys
import re

line_no = int(sys.stdin.readline().strip())
lines = []
for i in range(line_no):
    lines.append(sys.stdin.readline().strip())
text = '\n'.join(lines)

word_no = int(sys.stdin.readline().strip())
words = []
for i in range(word_no):
    words.append(sys.stdin.readline().strip())

cnt_by_word = {}
pattern = r'\w(' + '|'.join(words) + r')\w'
matches = re.findall(pattern, text, re.M | re.DOTALL)
for match in matches:
    if match not in cnt_by_word:
        cnt_by_word[match] = 0

    cnt_by_word[match] += 1

for word in words:
    if word in cnt_by_word:
        print cnt_by_word[word]
    else:
        print 0


