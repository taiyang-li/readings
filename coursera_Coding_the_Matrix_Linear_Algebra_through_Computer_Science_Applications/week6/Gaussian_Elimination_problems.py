# version code f4bde2e5d0a5+
coursera = 1
# Please fill out this stencil and submit using the provided submission script.

from matutil import *
from GF2 import one
from triangular import *



## 1: (Problem 1) Recognizing Echelon Form
# Write each matrix as a list of row lists

echelon_form_1 = [[1, 2, 0, 2, 0],
                  [0, 1, 0, 3, 4],
                  [0, 0, 2, 3, 4],
                  [0, 0, 0, 2, 0],
                  [0, 0, 0, 0, 4]]

echelon_form_2 = [[0, 4, 3, 4, 4],
                  [0, 0, 4, 2, 0],
                  [0, 0, 0, 0, 1],
                  [0, 0, 0, 0, 0]]

echelon_form_3 = [[1, 0, 0, 1],
                  [0, 0, 0, 1],
                  [0, 0, 0, 0]]

echelon_form_4 = [[1, 0, 0, 0],
                  [0, 1, 0, 0],
                  [0, 0, 0, 0],
                  [0, 0, 0, 0]]



## 2: (Problem 2) Is it echelon?
def is_echelon(A):
    '''
    
    Input:
        - A: a list of row lists
    Output:
        - True if A is in echelon form
        - False otherwise
    Examples:
        >>> is_echelon([[9,-1,2],[0,4,5],[0,0,2]])
        True
        >>> is_echelon([[0,4,5],[0,3,0],[0,0,2]])
        False
        >>> is_echelon([[9,10]])
        True
        >>> is_echelon([[5]])
        True
        >>> is_echelon([[1],[1]])
        False
        >>> is_echelon([[0]])
        True
        >>> is_echelon([[0],[1]])
        False
    '''
    nrow = len(A)
    ncol = len(A[0])
    for row in range(nrow):
        col = 0
        while col < ncol and A[row][col] == 0:
            col += 1
        if row > 0:
            if col < pre_col:
                return False
            elif col == pre_col and pre_col != ncol:
                return False
        pre_col = col
        
    return True
 
    
    
## 3: (Problem 3) Solving with Echelon Form: No Zero Rows
# Give each answer as a list
echelon_form_vec_a = [1, 0, 3, 0]
echelon_form_vec_b = [-3, 1, -2, 3]
echelon_form_vec_c = [-5, 0, 2, 0, 2]


## 4: (Problem 4) Solving with Echelon Form
# If a solution exists, give it as a list vector.
# If no solution exists, provide "None" (without the quotes).

solving_with_echelon_form_a = None
solving_with_echelon_form_b = [21, 0, 2, 0, 0]



## 5: (Problem 5) Echelon Solver
def echelon_solve(row_list, label_list, b):
    '''
    Input:
        - row_list: a list of Vecs
        - label_list: a list of labels establishing an order on the domain of
                      Vecs in row_list
        - b: a vector (represented as a list)
    Output:
        - Vec x such that row_list * x is b
    >>> D = {'A','B','C','D','E'}
    >>> U_rows = [Vec(D, {'A':one, 'E':one}), Vec(D, {'B':one, 'E':one}), Vec(D,{'C':one})]
    >>> b_list = [one,0,one]
    >>> cols = ['A', 'B', 'C', 'D', 'E']
    >>> echelon_solve(U_rows, cols, b_list) == Vec({'B', 'C', 'A', 'D', 'E'},{'B': 0, 'C': one, 'A': one})
    True
    '''
    '''
    col = len(label_list)
    row = len(row_list)
    A = []
    c = []
    i, j = 0, 0
    while i<col and j < row:
        tmp = row_list[j]
        for k in range(col):
            if tmp[label_list[k]] != 0:
                break
        print(i,j,k)
        # k is the position of entry 
        if i < k:
            A += [Vec(set(label_list), {})] * (k-i) 
            c += [0] * (k-i)
            i = k
        A.append(row_list[j])
        c.append(b[j])
        i += 1
        j += 1
    if i != col:
        A += [Vec(set(label_list), {})] * (col-i)
        c += [0] * (col-i)
    print(A)
    print(c)
    return triangular_solve(A, label_list, c)
    '''
    D = row_list[0].D
    x = Vec(D, {})
    for j in reversed(range(len(row_list))):
        row = row_list[j]
        entry = 0
        while entry < len(D):
            if row[label_list[entry]] != 0:
                break
            entry += 1
        
        if entry == len(D):
            if b[j] != 0:
                return None
            else:
                continue
        
        c = label_list[entry]
        x[c] = (b[j] - x*row) / row[c]
    
    return x
        
            
            



## 6: (Problem 6) Solving General Matrices via Echelon
row_list = [Vec({'A', 'B', 'C', 'D'}, {'A':one, 'B':one, 'D':one}),  \
            Vec({'A', 'B', 'C', 'D'}, {'B':one}),                  \
            Vec({'A', 'B', 'C', 'D'}, {'C':one}),                  \
            Vec({'A', 'B', 'C', 'D'}, {'D':one})]    # Provide as a list of Vec instances
label_list = ['A', 'B', 'C', 'D'] # Provide as a list
b = [one,one, 0, 0]          # Provide as a list of GF(2) values



## 7: (Problem 7) Nullspace A
null_space_rows_a = {3, 4} # Put the row numbers of M from the PDF



## 8: (Problem 8) Nullspace B
null_space_rows_b = {4} # Put the row numbers of M from the PDF

