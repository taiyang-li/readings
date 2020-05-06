#!/usr/bin/python 


s = {-4, -2,1,2,5,0}
r = []
for i in s:
    for j in s:
        for k in s: 
            if sum([i, j, k]) == 0:
                t = (i,j,k)
                r.append(t)

print r


