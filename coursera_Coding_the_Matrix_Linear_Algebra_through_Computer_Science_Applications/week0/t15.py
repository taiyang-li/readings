#!/usr/bin/python 


s = {-4, -2,1,2,5,0}
r = []
find = 0
for i in s:
    for j in s:
        for k in s: 
            if sum([i, j, k]) == 0:
                t = (i,j,k)
                r.append(t)
                find = 1
                break
        if find == 1:
            break
    if find == 1:
        break
        

print r


