#!/usr/bin/python

s = {1,2,3,4}
t = {3,4,5,6}

r = set()
for i in s:
    for j in t:
        if i == j:
            r.add(i)

print r
