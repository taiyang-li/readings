# version code 542eddf1f327+
coursera = 1
# Please fill out this stencil and submit using the provided submission script.

from vec import Vec
from mat import Mat
from bitutil import bits2mat, str2bits, noise
from GF2 import one
import matutil 

## Task 1
""" Create an instance of Mat representing the generator matrix G. You can use
the procedure listlist2mat in the matutil module (be sure to import first).
Since we are working over GF (2), you should use the value one from the
GF2 module to represent 1"""
G = matutil.listlist2mat([
    [one, 0, one, one], 
    [one, one, 0, one], 
    [0, 0, 0, one], 
    [one, one, one, 0], 
    [0, 0, one, 0], 
    [0, one, 0, 0], 
    [one, 0, 0, 0]])

## Task 2
# Please write your answer as a list. Use one from GF2 and 0 as the elements.
encoding_1001 = [0, 0, one, one, 0, 0, one]


## Task 3
# Express your answer as an instance of the Mat class.
R = matutil.listlist2mat([
    [0, 0, 0, 0, 0, 0, one], 
    [0, 0, 0, 0, 0, one, 0], 
    [0, 0, 0, 0, one, 0, 0], 
    [0, 0, one, 0, 0, 0, 0]])

## Task 4
# Create an instance of Mat representing the check matrix H.
H = matutil.listlist2mat([
    [0, 0, 0, one, one, one, one], 
    [0, one, one, 0, 0, one, one], 
    [one, 0, one, 0, one, 0, one]])

## Task 5
def find_error(e):
    """
    Input: an error syndrome as an instance of Vec
    Output: the corresponding error vector e
    input error syndrome  =  H * e 
    output  e 
    Examples:
        >>> find_error(Vec({0,1,2}, {0:one})) == Vec({0, 1, 2, 3, 4, 5, 6},{3: one})
        True
        >>> find_error(Vec({0,1,2}, {2:one})) == Vec({0, 1, 2, 3, 4, 5, 6},{0: one})
        True
        >>> find_error(Vec({0,1,2}, {1:one, 2:one})) == Vec({0, 1, 2, 3, 4, 5, 6},{2: one})   
        True
        >>> find_error(Vec({0,1,2}, {})) == Vec({0,1,2,3,4,5,6}, {})
        True
    """
    res = Vec({0,1,2,3,4,5,6}, {})
    d = matutil.mat2coldict(H)
    for k,v in d.items():
        if v == e:
            res[k] = one
    return res
    

## Task 6
# Use the Vec class for your answers.
non_codeword = Vec({0,1,2,3,4,5,6}, {0: one, 1:0, 2:one, 3:one, 4:0, 5:one, 6:one})
error_vector = Vec({0,1,2,3,4,5,6}, {6:one})
code_word = Vec({0,1,2,3,4,5,6}, {0:one, 2:one, 3:one, 5:one})
original = Vec({0,1,2,3}, {1:one, 3:one})


## Task 7
def find_error_matrix(S):
    """
    Input: a matrix S whose columns are error syndromes
    Output: a matrix whose cth column is the error corresponding to the cth column of S.
    Example:
        >>> S = listlist2mat([[0,one,one,one],[0,one,0,0],[0,0,0,one]])
        >>> find_error_matrix(S) == Mat(({0, 1, 2, 3, 4, 5, 6}, {0, 1, 2, 3}), {(1, 3): 0, (3, 0): 0, (2, 1): 0, (6, 2): 0, (5, 1): one, (0, 3): 0, (4, 0): 0, (1, 2): 0, (3, 3): 0, (6, 3): 0, (5, 0): 0, (2, 2): 0, (4, 1): 0, (1, 1): 0, (3, 2): one, (0, 0): 0, (6, 0): 0, (2, 3): 0, (4, 2): 0, (1, 0): 0, (5, 3): 0, (0, 1): 0, (6, 1): 0, (3, 1): 0, (2, 0): 0, (4, 3): one, (5, 2): 0, (0, 2): 0})
        True
    """
    # divide the matrix into cols 
    res = {}
    cols = matutil.mat2coldict(S)
    for i in range(len(S.D[1])):
        res[i] = find_error(cols[i])
    return matutil.coldict2mat(res)

## Task 8
s = "I'm trying to free your mind, Neo. But I can only show you the door. You're the one that has to walk through it."
P = bits2mat(str2bits(s))


## Task 9
C = G*P
bits_before = 896
bits_after = 1568


## Ungraded Task
CTILDE = C + noise(C,0.02) 

## Task 10
def correct(A):  
    """
    Input: a matrix A each column of which differs from a codeword in at most one bit
    Output: a matrix whose columns are the corresponding valid codewords.
    Example:
        >>> A = Mat(({0,1,2,3,4,5,6}, {1,2,3}), {(0,3):one, (2, 1): one, (5, 2):one, (5,3):one, (0,2): one})
        >>> correct(A) == Mat(({0, 1, 2, 3, 4, 5, 6}, {1, 2, 3}), {(0, 1): 0, (1, 2): 0, (3, 2): 0, (1, 3): 0, (3, 3): 0, (5, 2): one, (6, 1): 0, (3, 1): 0, (2, 1): 0, (0, 2): one, (6, 3): one, (4, 2): 0, (6, 2): one, (2, 3): 0, (4, 3): 0, (2, 2): 0, (5, 1): 0, (0, 3): one, (4, 1): 0, (1, 1): 0, (5, 3): one})
        True
    """
    return find_error_matrix(H*A)  + A 

