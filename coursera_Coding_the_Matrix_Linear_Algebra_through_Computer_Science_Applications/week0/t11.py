#!/usr/bin/python 

cl = ['A', 'B', 'C']
il = [1, 2, 3]
r = []
for c in cl:
    for i in il:
        tmp = [c, i]
        r.append(tmp)
        
print r
