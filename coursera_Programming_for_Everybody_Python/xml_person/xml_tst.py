#!/usr/local/bin/python

import xml.etree.ElementTree as ET

FILE = open("person.xml")
data = FILE.read();
tree = ET.fromstring(data)
print "name:", tree.find('name').text
print "attr:", tree.find('email').get('hide')

