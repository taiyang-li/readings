#!/usr/local/bin/python

import re
hand = open('mbox-short.txt')
for line in hand:
    line = line.rstrip()
    # if re.search('^F..m', line):
    # if re.search('F..m', line):
    # if re.search('^F..m.+@', line):
    x = re.findall('^(F..m)', line)
    if len(x) > 0:
        print x

s = 'hello from csev@unich.edu to cwen@iupui.edu about the meeting @2PM'
# lst = re.findall('\S+@\S+', s)
lst = re.findall('[a-zA-Z0-9]\S+@\S+[a-zA-Z0-9]', s)
print lst
