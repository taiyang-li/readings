#!/usr/bin/python 

l = [[.25, .75, .1], [-1, 0], [4, 4, 4, 4]] 
s = 0
for i in range(len(l)):
    s += sum(l[i])

print s
