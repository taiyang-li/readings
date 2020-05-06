#!/usr/bin/python 

import sys
import re

lines = []
words = []
expand_words = {}

line_no = int(sys.stdin.readline().strip())
for i in range(line_no):
    line = sys.stdin.readline().strip()
    lines.append(line)

word_no = int(sys.stdin.readline().strip())
for i in range(word_no):
    word = sys.stdin.readline().strip()
    words.append(word)

for word in words:
    new_word = re.sub(r'ze$', r'se', word)
    if new_word != word:
        expand_words[new_word] = word

# construct regular expression
pattern = r'\b(' + '|'.join(expand_words.keys() + expand_words.values()) + r')\b'
cnt_by_word = {}
for line in lines:
    matches = re.findall(pattern, line)
    for match in matches:
        if match in expand_words:
            origin_word = expand_words[match]
        else:
            origin_word = match

        if not origin_word in cnt_by_word:
            cnt_by_word[origin_word] = 1
        else:
            cnt_by_word[origin_word] += 1

for word in words:
    if not word in cnt_by_word:
        print 0
    else:
        print cnt_by_word[word]
