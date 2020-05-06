#!/usr/bin/python 

dlist = [{'James':'Sean', 'director':'Terence'}, {'James':'Roger',
    'director':'Lewis'}, {'James':'Pierce', 'director':'Roger'}]
k = 'James'
res = []
for dict in dlist:
    res.append(dict[k])

print res


