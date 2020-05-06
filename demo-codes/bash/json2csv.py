#!/usr/bin/env python 
# coding: utf-8

import json
import sys

input_file = sys.argv[1]
output_file = sys.argv[2]

# load json from file
with open(input_file) as f:
    data = json.load(f)

with open(output_file, 'w') as f:
    # write csv header
    header = data['headers']
    for table in header:
        fields = header[table]
        f.write('%s\n' % (','.join(fields)))
        break

    # write csv body
    row = data['rows']
    for table in row:
        values = row[table]
        for line in values:
            tmp = []
            for value in line:
                if isinstance(value, int) or isinstance(value, float):
                    tmp.append(str(value))
                elif isinstance(value, str) or isinstance(value, unicode):
                    tmp.append(value)
                else:
                    print "unknown type of value", str(values)
            f.write('%s\n' % (','.join(tmp)))
        break

