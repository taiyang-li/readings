#!/usr/bin/python 

a = [10, 25, 40]
b = [1, 15, 20]
c = zip(a,b)

print [x+y for (x,y) in c]
