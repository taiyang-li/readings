from factoring_lab import *

# from factoring_support import primes
# N = 2419
# primeset = primes(32)
# roots, rowlist = find_candidates(N, primeset)
# print(set(roots) == set([51, 52, 53, 58, 61, 62, 63, 67, 68, 71, 77, 79]))
# D = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}
# print(set(rowlist) == set([Vec(D,{2: one, 13: one, 7: one}),\
                # Vec(D,{3: one, 19: one, 5: one}),\
                # Vec(D,{2: one, 3: one, 5: one, 13: one}),\
                # Vec(D,{3: one, 5: one, 7: one}),\
                # Vec(D,{7: one, 2: one, 3: one, 31: one}),\
                # Vec(D,{3: one, 19: one}),\
                # Vec(D,{2: one, 31: one}),\
                # Vec(D,{2: one, 5: one, 23: one}),\
                # Vec(D,{5: one}),\
                # Vec(D,{3: one, 2: one, 19: one, 23: one}),\
                # Vec(D,{2: one, 3: one, 5: one, 13: one}),\
                # Vec(D,{2: one, 3: one, 13: one})]))

# roots = [51, 52, 53, 58, 61, 62, 63, 67, 68, 71, 77, 79]
# N = 2419
# v = Vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},{1: one, 2: one, 11: one, 5: one})  
# find_a_and_b(v, roots, N) == (13498888, 778050)
# v = Vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},{0: 0, 1: 0, 10: one, 2: one})
# find_a_and_b(v, roots, N) == (4081, 1170)

print(factor(2461799993978700679))