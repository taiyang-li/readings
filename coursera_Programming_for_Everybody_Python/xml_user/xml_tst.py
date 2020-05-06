#!/usr/local/bin/python

import xml.etree.ElementTree as ET

FILE = open("user.xml")
data = FILE.read();
stuff = ET.fromstring(data)
lst = stuff.findall('users/user')

for item in lst:
    print "name:", item.find('name').text
    print "id:", item.find('id').text
    print "attr:", item.get('x')



