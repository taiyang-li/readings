#!/usr/local/bin/python

import json

FILE = open('user.json')
input = FILE.read()
info = json.loads(input)
print 'User count: ', len(info)

for item in info:
    print 'Name', item['name']
    print 'Id', item['id']
    print "Attr", item['x']
