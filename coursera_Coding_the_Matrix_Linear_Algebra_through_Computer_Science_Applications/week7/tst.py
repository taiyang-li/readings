
from  Orthogonalization_problems import *
f = open("age-height.txt")

line = f.readline()
age = []
height = []

while line:
    line = line.strip('\n')
    age_height = line.split('\t') 
    print(age_height)
    age.append(int(age_height[0]))
    height.append(float(age_height[1]))
    line = f.readline()
print(age)
print(height)

Height =list2vec(height)
Age = list2vec(age)
One = list2vec([1] * len(age))

Age_One = coldict2mat([Age, One])
print(Age_One)
print(Height)
print(QR_solve(Age_One, Height))


# L = [list2vec(v) for v in [[6, 2, 3],[6, 0, 3]]]
# L = [list2vec(v) for v in [[2, 2, 1],[3, 1, 1]]]
# Q, R = aug_orthonormalize(L)
# print(coldict2mat(Q)) 
# print(coldict2mat(R))

# domain = ({'a','b','c'},{'A','B'})
# A = Mat(domain,{('a','A'):-1, ('a','B'):2,('b','A'):5, ('b','B'):3,('c','A'):1,('c','B'):-2})
# Q, R = QR_factor(A)
# b = Vec(domain[0], {'a': 1, 'b': -1})
# x = QR_solve(A, b)
# print(x)
# result = A.transpose()*(b-A*x)
# print(result.is_almost_zero())

# print(QR_solve(least_squares_A1, least_squares_b1))
# print(QR_solve(least_squares_A2, least_squares_b2))

# least_squares_A2 = listlist2mat([[3, 1], [4, 1]])
# least_squares_b2 = list2vec([10,13])
# print(QR_solve(least_squares_A2, least_squares_b2))








    
    