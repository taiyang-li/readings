#!/bin/env python

import sys
import os

filepath = os.environ["map_input_file"]
filename = os.path.split(filepath)[-1]
if filename == "data_info":
	type = "1"
else:
	type = "2"

# type = "2"
for line in sys.stdin:
	line = line.strip()
	if len(line) == 0:
		continue

	fields = line.split(' ')
	if len(fields) < 2:
		continue

	print "%s %s %s" % (fields[0], type, ' '.join(fields[1:]))
