#!/usr/bin/python

def row(p, n): 
    return [ i+p for i in range(n)]


def matrix(m, n):   
    res = []
    for i in range(m):
        res.append(row(i,n))
    return res


print matrix(4,4)
