#!/usr/bin/python

def add_by1(x):
    return x+1;

domain = range(1,6)
pr = [0.5, 0.2, 0.1, 0.1, 0.1, 0.1]
res = 0.0

for i in range(len(domain)):
    x = domain[i]
    y = add_by1(x)
    
    if y%2==0:
        res += pr[i]
print res
