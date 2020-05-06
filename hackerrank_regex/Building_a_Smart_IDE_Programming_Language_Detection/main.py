#!/usr/bin/python 

import sys
import re

lines = sys.stdin.readlines()
text = ''
for line in lines:
    text += line

c_cnt = re.findall(r'\b#include|typedef|scanf|\s+printf|int main\(\b', text, re.M | re.DOTALL)
java_cnt = re.findall(r'public class|public static void main\(|System\.out\.println|import java\b', text, re.M | re.DOTALL)
python_cnt = re.findall(r'^\t*def\s+\w+\(|^\t*class [\w\(\)]+:$|__name__\s*==\s*\'__main__\'|^\t*print ', text, re.M |re.DOTALL)

"""
print c_cnt
print java_cnt
print python_cnt
"""

if len(c_cnt) > 0:
    print "C"
elif len(java_cnt) > 0:
    print "Java"
elif len(python_cnt) > 0:
    print "Python"
else:
    print "Impossible"

