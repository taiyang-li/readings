#!/usr/bin/python 


dlist = [{'Bilbo':'Ian','Frodo':'Elijah'},
        {'Bilbo':'Martin','Thorin':'Richard'}]
#k = 'Bilbo' 
k = 'Frodo' 
r = []
for dict in dlist:
    if k in dict:
        r.append(dict[k])  
    else:
        r.append("NOT PRESENT")

print r
