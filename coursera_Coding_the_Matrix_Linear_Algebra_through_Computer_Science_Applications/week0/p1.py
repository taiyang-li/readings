#!/usr/bin/python

def tuple_sum(A,B):
    res = []
    for i in range(len(A)):
        t = []
        for j in range(len(A[i])):
            t.append(A[i][j] + B[i][j])
        t = tuple(t)
        res.append(t)
    return res 


A = [(1,2), (10, 20)]
B = [(3,4), (30, 40)]

print tuple_sum(A, B)
            
