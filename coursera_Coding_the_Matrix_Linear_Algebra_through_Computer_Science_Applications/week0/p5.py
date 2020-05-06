#!/usr/bin/python


domain = range(1,7)
pr = [0.2, 0.2, 0.2, 0.1, 0.1, 0.1, 0.1] 
res = 0.0

for i in range(len(domain)):
    x = domain[i]
    if x%3==1:
        res += pr[i]
print res
