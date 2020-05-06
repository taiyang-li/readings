#!/bin/env python

import sys

current_word = None
current_count = None

for line in sys.stdin:
	line = line.strip()
	word, count = line.split('\t')
	count = int(count)
	
	if current_word == word:
		current_count += count
		continue
	
	if current_word is None:
		current_word = word
		current_count = count
		continue
	
	print "%s\t%d" % (current_word, current_count)
	current_word = word
	current_count = count


