# version code 542eddf1f327+
coursera = 1
# Please fill out this stencil and submit using the provided submission script.

# Copyright 2013 Philip N. Klein
from vec import Vec
from GF2 import one

#Test your Mat class over R and also over GF(2).  The following tests use only R.

def equal(A, B):
    """
    Returns true iff A is equal to B.

    >>> Mat(({'a','b'}, {0,1}), {('a',1):0}) == Mat(({'a','b'}, {0,1}), {('b',1):0})
    True
    >>> A = Mat(({'a','b'}, {0,1}), {('a',1):2, ('b',0):1})
    >>> B = Mat(({'a','b'}, {0,1}), {('a',1):2, ('b',0):1, ('b',1):0})
    >>> C = Mat(({'a','b'}, {0,1}), {('a',1):2, ('b',0):1, ('b',1):5})
    >>> A == B
    True
    >>> A == C
    False
    >>> A == Mat(({'a','b'}, {0,1}), {('a',1):2, ('b',0):1})
    True
    """
    assert A.D == B.D
    
    for r in A.D[0]:
        for c in A.D[1]:
            if A[r,c] != B[r,c]:
                return False
    return True

def getitem(M, k):
    """
    Returns the value of entry k in M, where k is a 2-tuple
    >>> M = Mat(({1,3,5}, {'a'}), {(1,'a'):4, (5,'a'): 2})
    >>> M[1,'a']
    4
    >>> M[3,'a']
    0
    """
    assert k[0] in M.D[0] and k[1] in M.D[1]  # index must be in right range
    if k in M.f.keys():
        return M.f[k]
    else:
        return 0

def setitem(M, k, val):
    """
    Set entry k of Mat M to val, where k is a 2-tuple.
    >>> M = Mat(({'a','b','c'}, {5}), {('a', 5):3, ('b', 5):7})
    >>> M['b', 5] = 9
    >>> M['c', 5] = 13
    >>> M == Mat(({'a','b','c'}, {5}), {('a', 5):3, ('b', 5):9, ('c',5):13})
    True

    Make sure your operations work with bizarre and unordered keys.

    >>> N = Mat(({((),), 7}, {True, False}), {})
    >>> N[(7, False)] = 1
    >>> N[(((),), True)] = 2
    >>> N == Mat(({((),), 7}, {True, False}), {(7,False):1, (((),), True):2})
    True
    """
    assert k[0] in M.D[0] and k[1] in M.D[1]
    M.f[k] = val

def add(A, B):
    """
    Return the sum of Mats A and B.
    >>> A1 = Mat(({3, 6}, {'x','y'}), {(3,'x'):-2, (6,'y'):3})
    >>> A2 = Mat(({3, 6}, {'x','y'}), {(3,'y'):4})
    >>> B = Mat(({3, 6}, {'x','y'}), {(3,'x'):-2, (3,'y'):4, (6,'y'):3})
    >>> A1 + A2 == B
    True
    >>> A2 + A1 == B
    True
    >>> A1 == Mat(({3, 6}, {'x','y'}), {(3,'x'):-2, (6,'y'):3})
    True
    >>> zero = Mat(({3,6}, {'x','y'}), {})
    >>> B + zero == B
    True
    >>> C1 = Mat(({1,3}, {2,4}), {(1,2):2, (3,4):3})
    >>> C2 = Mat(({1,3}, {2,4}), {(1,4):1, (1,2):4})
    >>> D = Mat(({1,3}, {2,4}), {(1,2):6, (1,4):1, (3,4):3})
    >>> C1 + C2 == D
    True
    """
    assert A.D == B.D
    res = Mat(A.D, {})
    
    for r in A.D[0]:
        for c in B.D[1]:
            res[r,c] = A[r,c] + B[r,c]
    return res

def scalar_mul(M, x):
    """
    Returns the result of scaling M by x.

    >>> M = Mat(({1,3,5}, {2,4}), {(1,2):4, (5,4):2, (3,4):3})
    >>> 0*M == Mat(({1, 3, 5}, {2, 4}), {})
    True
    >>> 1*M == M
    True
    >>> 0.25*M == Mat(({1,3,5}, {2,4}), {(1,2):1.0, (5,4):0.5, (3,4):0.75})
    True
    """
    res = Mat(M.D, {})
    for idx in M.f.keys():
        res[idx] = x * M[idx]
    return res

def transpose(M):
    """
    Returns the matrix that is the transpose of M.

    >>> M = Mat(({0,1}, {0,1}), {(0,1):3, (1,0):2, (1,1):4})
    >>> M.transpose() == Mat(({0,1}, {0,1}), {(0,1):2, (1,0):3, (1,1):4})
    True
    >>> M = Mat(({'x','y','z'}, {2,4}), {('x',4):3, ('x',2):2, ('y',4):4, ('z',4):5})
    >>> Mt = Mat(({2,4}, {'x','y','z'}), {(4,'x'):3, (2,'x'):2, (4,'y'):4, (4,'z'):5})
    >>> M.transpose() == Mt
    True
    """
    res = Mat((M.D[1], M.D[0]), {})
    
    for r in M.D[0]:
        for c in M.D[1]:
            res[c,r] = M[r,c]
    return res
    
def vector_matrix_mul(v, M):
    """
    returns the product of vector v and matrix M

    >>> v1 = Vec({1, 2, 3}, {1: 1, 2: 8})
    >>> M1 = Mat(({1, 2, 3}, {'a', 'b', 'c'}), {(1, 'b'): 2, (2, 'a'):-1, (3, 'a'): 1, (3, 'c'): 7})
    >>> v1*M1 == Vec({'a', 'b', 'c'},{'a': -8, 'b': 2, 'c': 0})
    True
    >>> v1 == Vec({1, 2, 3}, {1: 1, 2: 8})
    True
    >>> M1 == Mat(({1, 2, 3}, {'a', 'b', 'c'}), {(1, 'b'): 2, (2, 'a'):-1, (3, 'a'): 1, (3, 'c'): 7})
    True
    >>> v2 = Vec({'a','b'}, {})
    >>> M2 = Mat(({'a','b'}, {0, 2, 4, 6, 7}), {})
    >>> v2*M2 == Vec({0, 2, 4, 6, 7},{})
    True
    """
    assert M.D[0] == v.D  # if not equal, then nonsense
    
    res = Vec(M.D[1], {})  # length of result  equals M.D[1]
    # traverse all the column of M
    for c in M.D[1]:
        res[c] = 0
        for r in M.D[0]:
            res[c] = res[c] + M[r,c] * v[r]
    return res

def matrix_vector_mul(M, v):
    """
    Returns the product of matrix M and vector v.
    >>> N1 = Mat(({1, 3, 5, 7}, {'a', 'b'}), {(1, 'a'): -1, (1, 'b'): 2, (3, 'a'): 1, (3, 'b'):4, (7, 'a'): 3, (5, 'b'):-1})
    >>> u1 = Vec({'a', 'b'}, {'a': 1, 'b': 2})
    >>> N1*u1 == Vec({1, 3, 5, 7},{1: 3, 3: 9, 5: -2, 7: 3})
    True
    >>> N1 == Mat(({1, 3, 5, 7}, {'a', 'b'}), {(1, 'a'): -1, (1, 'b'): 2, (3, 'a'): 1, (3, 'b'):4, (7, 'a'): 3, (5, 'b'):-1})
    True
    >>> u1 == Vec({'a', 'b'}, {'a': 1, 'b': 2})
    True
    >>> N2 = Mat(({('a', 'b'), ('c', 'd')}, {1, 2, 3, 5, 8}), {})
    >>> u2 = Vec({1, 2, 3, 5, 8}, {})
    >>> N2*u2 == Vec({('a', 'b'), ('c', 'd')},{})
    True
    """
    assert M.D[1] == v.D
    
    res = Vec(M.D[0], {})
    for r in M.D[0]:
        res[r] = 0
        for c in M.D[1]: 
            res[r] = res[r] + M[r,c] * v[c]
    return res

def matrix_matrix_mul(A, B):
    """
    Returns the result of the matrix-matrix multiplication, A*B.

    >>> A = Mat(({0,1,2}, {0,1,2}), {(1,1):4, (0,0):0, (1,2):1, (1,0):5, (0,1):3, (0,2):2})
    >>> B = Mat(({0,1,2}, {0,1,2}), {(1,0):5, (2,1):3, (1,1):2, (2,0):0, (0,0):1, (0,1):4})
    >>> A*B == Mat(({0,1,2}, {0,1,2}), {(0,0):15, (0,1):12, (1,0):25, (1,1):31})
    True
    >>> C = Mat(({0,1,2}, {'a','b'}), {(0,'a'):4, (0,'b'):-3, (1,'a'):1, (2,'a'):1, (2,'b'):-2})
    >>> D = Mat(({'a','b'}, {'x','y'}), {('a','x'):3, ('a','y'):-2, ('b','x'):4, ('b','y'):-1})
    >>> C*D == Mat(({0,1,2}, {'x','y'}), {(0,'y'):-5, (1,'x'):3, (1,'y'):-2, (2,'x'):-5})
    True
    >>> M = Mat(({0, 1}, {'a', 'c', 'b'}), {})
    >>> N = Mat(({'a', 'c', 'b'}, {(1, 1), (2, 2)}), {})
    >>> M*N == Mat(({0,1}, {(1,1), (2,2)}), {})
    True
    >>> E = Mat(({'a','b'},{'A','B'}), {('a','A'):1,('a','B'):2,('b','A'):3,('b','B'):4})
    >>> F = Mat(({'A','B'},{'c','d'}),{('A','d'):5})
    >>> E*F == Mat(({'a', 'b'}, {'d', 'c'}), {('b', 'd'): 15, ('a', 'd'): 5})
    True
    >>> F.transpose()*E.transpose() == Mat(({'d', 'c'}, {'a', 'b'}), {('d', 'b'): 15, ('d', 'a'): 5})
    True
    """
    assert A.D[1] == B.D[0]   
    
    res = Mat((A.D[0], B.D[1]), {})
    for r in A.D[0]:
        for c in B.D[1]:
            res[r,c] = 0
            for l in A.D[1]:
                res[r,c] = res[r,c] + A[r,l] * B[l,c]
    return res

################################################################################

class Mat:
    def __init__(self, labels, function):
        self.D = labels
        self.f = function

    __getitem__ = getitem
    __setitem__ = setitem
    transpose = transpose

    def __neg__(self):
        return (-1)*self

    def __mul__(self,other):
        if Mat == type(other):
            return matrix_matrix_mul(self,other)
        elif Vec == type(other):
            return matrix_vector_mul(self,other)
        else:
            return scalar_mul(self,other)
            #this will only be used if other is scalar (or not-supported). mat and vec both have __mul__ implemented

    def __rmul__(self, other):
        if Vec == type(other):
            return vector_matrix_mul(other, self)
        else:  # Assume scalar
            return scalar_mul(self, other)

    __add__ = add

    def __radd__(self, other):
        "Hack to allow sum(...) to work with matrices"
        if other == 0:
            return self

    def __sub__(a,b):
        return a+(-b)

    __eq__ = equal

    def copy(self):
        return Mat(self.D, self.f.copy())

    def __str__(M, rows=None, cols=None):
        "string representation for print()"
        if rows == None: rows = sorted(M.D[0], key=repr)
        if cols == None: cols = sorted(M.D[1], key=repr)
        separator = ' | '
        numdec = 3
        pre = 1+max([len(str(r)) for r in rows])
        colw = {col:(1+max([len(str(col))] + [len('{0:.{1}G}'.format(M[row,col],numdec)) if isinstance(M[row,col], int) or isinstance(M[row,col], float) else len(str(M[row,col])) for row in rows])) for col in cols}
        s1 = ' '*(1+ pre + len(separator))
        s2 = ''.join(['{0:>{1}}'.format(str(c),colw[c]) for c in cols])
        s3 = ' '*(pre+len(separator)) + '-'*(sum(list(colw.values())) + 1)
        s4 = ''.join(['{0:>{1}} {2}'.format(str(r), pre,separator)+''.join(['{0:>{1}.{2}G}'.format(M[r,c],colw[c],numdec) if isinstance(M[r,c], int) or isinstance(M[r,c], float) else '{0:>{1}}'.format(M[r,c], colw[c]) for c in cols])+'\n' for r in rows])
        return '\n' + s1 + s2 + '\n' + s3 + '\n' + s4

    def pp(self, rows, cols):
        print(self.__str__(rows, cols))

    def __repr__(self):
        "evaluatable representation"
        return "Mat(" + str(self.D) +", " + str(self.f) + ")"

    def __iter__(self):
        raise TypeError('%r object is not iterable' % self.__class__.__name__)
