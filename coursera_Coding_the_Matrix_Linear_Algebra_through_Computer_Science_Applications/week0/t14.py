#!/usr/bin/python 


s = {-4, -2,1,2,5,0}
r = []
for i in s:
    for j in s:
        for k in s: 
            if i == 0 and j == 0 and k == 0:
                continue

            if sum([i, j, k]) == 0:
                t = (i,j,k)
                r.append(t)

        


