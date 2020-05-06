#!/bin/env python

import sys

last_fields = None
for line in sys.stdin:
	line = line.strip()
	if len(line) == 0:
		continue
	
	fields = line.split(' ')
	if len(fields) < 2:
		continue

	type = fields[1]
	if not (type == '1' and len(fields) == 3 or
			type == '2' and len(fields) == 4):
		continue
	
	if type == '2':
		if not last_fields is None:
			if last_fields[0] == fields[0] and last_fields[1] == '1':
				print "%s %s %s %s" % (last_fields[0], last_fields[2], fields[2], fields[3])
	last_fields = fields
	

