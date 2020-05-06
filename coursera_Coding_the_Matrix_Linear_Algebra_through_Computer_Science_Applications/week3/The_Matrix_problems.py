# version code 542eddf1f327+
coursera = 1
# Please fill out this stencil and submit using the provided submission script.

from mat import Mat
from vec import Vec
import matutil 



## 1: (Problem 4.17.1) Computing matrix-vector products
# Please represent your solution vectors as lists.
vector_matrix_product_1 = [1, 0]
vector_matrix_product_2 = [0, 4.44]
vector_matrix_product_3 = [14, 20, 26]



## 2: (Problem 4.17.2) Matrix-vector multiplication to swap entries
# Represent your solution as a list of rowlists.
# For example, the 2x2 identity matrix would be [[1,0],[0,1]].

M_swap_two_vector = [[0,1], [1,0]]



## 3: (Problem 4.17.3) [z+x, y, x] Matrix-vector multiplication
three_by_three_matrix =  [[1,0,1], [0,1,0], [1,0,0]] # Represent with a list of rowlists.



## 4: (Problem 4.17.4) [2x, 4y, 3z] matrix-vector multiplication
multiplied_matrix = [[2,0,0], [0,4,0], [0,0,3]] # Represent with a list of row lists.



## 5: (Problem 4.17.5) Matrix multiplication: dimension of matrices
# Please enter a boolean representing if the multiplication is valid.
# If it is not valid, please enter None for the dimensions.

part_1_valid = False # True or False
part_1_number_rows = None # Integer or None
part_1_number_cols = None # Integer or None

part_2_valid = False
part_2_number_rows = None
part_2_number_cols = None

part_3_valid = True
part_3_number_rows = 1
part_3_number_cols = 2

part_4_valid = True
part_4_number_rows = 2
part_4_number_cols = 1

part_5_valid = False
part_5_number_rows = None
part_5_number_cols = None

part_6_valid = True
part_6_number_rows = 1
part_6_number_cols = 1

part_7_valid = True
part_7_number_rows = 3
part_7_number_cols = 3



## 6: (Problem 4.17.6) Matrix-matrix multiplication practice with small matrices
# Please represent your answer as a list of row lists.
# Example: [[1,1],[2,2]]
small_mat_mult_1 = [[8, 13], [8, 14]]
small_mat_mult_2 = [[24, 11, 4], [1, 3, 0]]
small_mat_mult_3 = [[3, 13]]
small_mat_mult_4 = [[14]]
small_mat_mult_5 = [[1,2,3], [2,4,6], [3,6,9]]
small_mat_mult_6 = [[-2, 4], [1, 1], [1, -3]]



## 7: (Problem 4.17.7) Matrix-matrix multiplication practice with a permutation matrix
# Please represent your solution as a list of row lists.

part_1_AB = [[5, 2, 0, 1], [2, 1, -4, 6], [2, 3, 0, -4], [-2, 3, 4, 0]]
part_1_BA = [[1, -4, 6, 2], [3, 0, -4, 2], [3, 4, 0, -2], [2, 0, 1, 5]]

part_2_AB = [[5, 1, 0, 2], [2, 6, -4, 1], [2, -4, 0, 3], [-2, 0, 4, 3]]
part_2_BA = [[3, 4, 0, -2], [3, 0, -4, 2], [1, -4, 6, 2], [2, 0, 1, 5]]

part_3_AB = [[1, 0, 5, 2], [6, -4, 2, 1], [-4, 0, 2, 3], [0, 4, -2, 3]]
part_3_BA = [[3, 4, 0, -2], [1, -4, 6, 2], [2, 0, 1, 5], [3, 0, -4, 2]]



## 8: (Problem 4.17.9) Matrix-matrix multiplication practice with very sparse matrices
# Please represent your answer as a list of row lists.

your_answer_a_AB = [[0, 0, 2, 0], [0, 0, 5, 0], [0, 0, 4, 0], [0, 0, 6, 0]]
your_answer_a_BA = [[0, 0, 0, 0], [4, 4, 4, 0], [0, 0, 0, 0], [0, 0, 0, 0]]

your_answer_b_AB = [[0, 2, -1, 0], [0, 5, 3, 0], [0, 4, 0, 0], [0, 6, -5, 0]]
your_answer_b_BA = [[0, 0, 0, 0], [1, 5, -2, 3], [0, 0, 0, 0], [4, 4, 4, 0]]

your_answer_c_AB = [[6, 0, 0, 0], [6, 0, 0, 0], [8, 0, 0, 0], [5, 0, 0, 0]]
your_answer_c_BA = [[4, 2, 1, -1], [4, 2, 1, -1], [0, 0, 0, 0], [0, 0, 0, 0]]

your_answer_d_AB = [[0, 3, 0, 4], [0, 4, 0, 1], [0, 4, 0, 4], [0, -6, 0, -1]]
your_answer_d_BA = [[0, 11, 0, -2], [0, 0, 0, 0], [0, 0, 0, 0], [1, 5, -2, 3]]

your_answer_e_AB = [[0, 3, 0, 8], [0, -9, 0, 2], [0, 0, 0, 8], [0, 15, 0, -2]]
your_answer_e_BA = [[-2, 12, 4, -10], [0, 0, 0, 0], [0, 0, 0, 0], [-3, -15, 6, -9]]

your_answer_f_AB = [[-4, 4, 2, -3], [-1, 10, -4, 9], [-4, 8, 8, 0], [1, 12, 4, -15]]
your_answer_f_BA = [[-4, -2, -1, 1], [2, 10, -4, 6], [8, 8, 8, 0], [-3, 18, 6, -15]]



## 9: (Problem 4.17.11) Column-vector and row-vector matrix multiplication
column_row_vector_multiplication1 = Vec({0, 1}, {0:13, 1:20})

column_row_vector_multiplication2 = Vec({0, 1, 2}, {0:24, 1:11, 2:4})

column_row_vector_multiplication3 = Vec({0, 1, 2, 3}, {0:4, 1:8, 2:11, 3:3})

column_row_vector_multiplication4 = Vec({0,1}, {0:30, 1:16})

column_row_vector_multiplication5 = Vec({0, 1, 2}, {0:-3, 1:1, 2:9})



## 10: (Problem 4.17.13) Linear-combinations matrix-vector multiply
# You are also allowed to use the matutil module
def lin_comb_mat_vec_mult(M, v): 
    '''
    Input:
      -M: a matrix
      -v: a vector
    Output: M*v
    The following doctests are not comprehensive; they don't test the
    main question, which is whether the procedure uses the appropriate
    linear-combination definition of matrix-vector multiplication. 
    Examples:
    >>> M=Mat(({'a','b'},{0,1}), {('a',0):7, ('a',1):1, ('b',0):-5, ('b',1):2})
    >>> v=Vec({0,1},{0:4, 1:2})
    >>> lin_comb_mat_vec_mult(M,v) == Vec({'a', 'b'},{'a': 30, 'b': -16})
    True
    >>> M1=Mat(({'a','b'},{0,1}), {('a',0):8, ('a',1):2, ('b',0):-2, ('b',1):1})
    >>> v1=Vec({0,1},{0:4,1:3})
    >>> lin_comb_mat_vec_mult(M1,v1) == Vec({'a', 'b'},{'a': 38, 'b': -5})
    True
    '''
    assert(M.D[1] == v.D)  # the lables must be the same 
    # you must use the definition of linear combination
    res = Vec(M.D[0], {})  # the result is a vector  
    cols = matutil.mat2coldict(M) 
    
    for lb in v.D:
        res = res + v[lb] * cols[lb]
    return res  
     
    



## 11: (Problem 4.17.14) Linear-combinations vector-matrix multiply
def lin_comb_vec_mat_mult(v, M):
    '''
    Input:
      -v: a vector
      -M: a matrix
    Output: v*M
    The following doctests are not comprehensive; they don't test the
    main question, which is whether the procedure uses the appropriate
    linear-combination definition of vector-matrix multiplication. 
    Examples:
      >>> M=Mat(({'a','b'},{0,1}), {('a',0):7, ('a',1):1, ('b',0):-5, ('b',1):2})
      >>> v=Vec({'a','b'},{'a':2, 'b':-1})
      >>> lin_comb_vec_mat_mult(v,M) == Vec({0, 1},{0: 19, 1: 0})
      True
      >>> M1=Mat(({'a','b'},{0,1}), {('a',0):8, ('a',1):2, ('b',0):-2, ('b',1):1})
      >>> v1=Vec({'a','b'},{'a':4,'b':3})
      >>> lin_comb_vec_mat_mult(v1,M1) == Vec({0, 1},{0: 26, 1: 11})
      True
    '''
    assert(v.D == M.D[0])  
    res = Vec(M.D[1], {})
    rows = matutil.mat2rowdict(M)
    for lb in  v.D:
        res = res + v[lb] * rows[lb]
    return res
    



## 12: (Problem 4.17.15) dot-product matrix-vector multiply
# You are also allowed to use the matutil module
def dot_product_mat_vec_mult(M, v): 
    '''
    Return the matrix-vector product M*v.
    The following doctests are not comprehensive; they don't test the
    main question, which is whether the procedure uses the appropriate
    dot-product definition of matrix-vector multiplication. 
    Examples:
    >>> M=Mat(({'a','b'},{0,1}), {('a',0):7, ('a',1):1, ('b',0):-5, ('b',1):2})
    >>> v=Vec({0,1},{0:4, 1:2})
    >>> dot_product_mat_vec_mult(M,v) == Vec({'a', 'b'},{'a': 30, 'b': -16})
    True
    >>> M1=Mat(({'a','b'},{0,1}), {('a',0):8, ('a',1):2, ('b',0):-2, ('b',1):1})
    >>> v1=Vec({0,1},{0:4,1:3})
    >>> dot_product_mat_vec_mult(M1,v1) == Vec({'a', 'b'},{'a': 38, 'b': -5})
    True
    '''
    assert(M.D[1] == v.D) 
    res = Vec(M.D[0], {})
    rows = matutil.mat2rowdict(M)
    
    for lb in M.D[0]:
        res[lb] = rows[lb] * v
    return res
    
    
    # using dot_product to calculate the result 
    


## 13: (Problem 4.17.16) Dot-product vector-matrix multiply
# You are also allowed to use the matutil module
def dot_product_vec_mat_mult(v, M):
    '''
    The following doctests are not comprehensive; they don't test the
    main question, which is whether the procedure uses the appropriate
    dot-product definition of vector-matrix multiplication. 
    Examples:
      >>> M=Mat(({'a','b'},{0,1}), {('a',0):7, ('a',1):1, ('b',0):-5, ('b',1):2})
      >>> v=Vec({'a','b'},{'a':2, 'b':-1})
      >>> dot_product_vec_mat_mult(v,M) == Vec({0, 1},{0: 19, 1: 0})
      True
      >>> M1=Mat(({'a','b'},{0,1}), {('a',0):8, ('a',1):2, ('b',0):-2, ('b',1):1})
      >>> v1=Vec({'a','b'},{'a':4,'b':3})
      >>> dot_product_vec_mat_mult(v1,M1) == Vec({0, 1},{0: 26, 1: 11})
      True
      '''
    assert(v.D == M.D[0])
    res = Vec(M.D[1], {})
    cols = matutil.mat2coldict(M)
    
    for lb in M.D[1]:
        res[lb] = cols[lb] * v
    
    return res
    
    



## 14: (Problem 4.17.17) Matrix-vector matrix-matrix multiply
# You are also allowed to use the matutil module
def Mv_mat_mat_mult(A, B):
    assert A.D[1] == B.D[0]
    # calculate the result of mat mul mat using the definjition of mat mul v 
    
    res = {} 
    
    # first divided B into cols
    cols = matutil.mat2coldict(B)
    
    # second using the method of mat mul v 
    
    for lb in B.D[1]:
        res[lb] = A * cols[lb]
        
    return matutil.coldict2mat(res)
    



## 15: (Problem 4.17.18) Vector-matrix matrix-matrix multiply
def vM_mat_mat_mult(A, B):
    assert A.D[1] == B.D[0]
    
    res = {}
    
    # first divide A into rows
    rows = matutil.mat2rowdict(A)
    
    # second using the method of v mul mat
    for lb in A.D[0]:
        res[lb] = rows[lb] * B
        
    return matutil.rowdict2mat(res)



## 16: () Buttons
from solver import solve
from GF2 import one

def D(n): return {(i,j) for i in range(n) for j in range(n)}

def button_vectors(n):
  return {(i,j):Vec(D(n),dict([((x,j),one) for x in range(max(i-1,0), min(i+2,n))]
                           +[((i,y),one) for y in range(max(j-1,0), min(j+2,n))]))
                           for (i,j) in D(n)}
                         
# Remind yourself of the types of the arguments to solve().

## PART 1

b1=Vec(D(9),{(7, 8):one,(7, 7):one,(6, 2):one,(3, 7):one,(2, 5):one,(8, 5):one,(1, 2):one,(7, 2):one,(6, 3):one,(0, 4):one,(2, 2):one,(5, 0):one,(6, 4):one,(0, 0):one,(5, 4):one,(1, 4):one,(8, 7):one,(0, 8):one,(6, 5):one,(2, 7):one,(8, 3):one,(7, 0):one,(4, 6):one,(6, 8):one,(0, 6):one,(1, 8):one,(7, 4):one,(2, 4):one})


#Solution given by solver.
#x1 = solve(button_vectors(9), b1)
x1 = ...

#residual
#r1 = b1 - button_vectors(9) * x1 
r1 = ...

#Is x1 really a solution? Assign True if yes, False if no.
#is_good1 = True if  r1 == Vec(D(9), {}) else False
is_good1 = ...

## PART 2

b2=Vec(D(9), {(3,4):one, (6,7):one})

#Solution given by solver
#x2 = solve(button_vectors(9), b2)
x2 = ...

#residual
#r2 = b2 - button_vectors(9) * x2
r2 = ...

#Is it really a solution? Assign True if yes, False if no.
#is_good2 = True if r2 == Vec(D(9), {}) else False
is_good2 = ...



## 17: (Problem 4.17.21) Solving 2x2 linear systems and finding matrix inverse
solving_systems_x1 = -0.2 
solving_systems_x2 =  0.4 
solving_systems_y1 =  0.8
solving_systems_y2 = -0.6
solving_systems_m = Mat(({0,1}, {0,1}), {(0,0):-0.2, (0,1):0.8, (1,0):0.4, (1,1):-0.6})  
solving_systems_a = Mat(({0,1}, {0,1}), {(0,0):3, (0,1):4, (1,0):2, (1,1):1})
solving_systems_a_times_m = Mat(({0, 1}, {0, 1}), {(0,0):1, (1,1):1})
solving_systems_m_times_a = Mat(({0, 1}, {0, 1}), {(0,0):1, (1,1):1})



## 18: (Problem 4.17.22) Matrix inverse criterion
# Please write your solutions as booleans (True or False)

are_inverses1 = True
are_inverses2 = True
are_inverses3 = False
are_inverses4 = False

