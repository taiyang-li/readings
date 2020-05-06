#!/usr/bin/env python
# coding: utf-8


import re
Test_String = raw_input()
Regex_Pattern = r'(\w)(?!\1)'
match = re.findall(Regex_Pattern, Test_String)
print "Number of matches :", len(match)
