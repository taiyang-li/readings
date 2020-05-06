#!/usr/bin/python 

s = 3 
b = 2 

dict = {}
for i in range(b**s):
    l = []
    for j in range(s):
        l.append(j%b)
        j /= b
    l.reverse()
    dict[i] = tuple(l)

print dict

s = 3 
b = 10

dict = {}
for i in range(b**s):
    l = []
    for j in range(s):
        l.append(j%b)
        j /= b
    l.reverse()
    dict[i] = tuple(l)

print dict


