# version code 3ebd92e7eece+
coursera = 1
# Please fill out this stencil and submit using the provided submission script.

import random
from GF2 import one
from vec import Vec
from vecutil import list2vec
import itertools
from The_Basis_problems import is_independent 


## 1: (Task 1) Choosing a Secret Vector
def randGF2(): return random.randint(0,1)*one

a0 = list2vec([one, one,   0, one,   0, one])
b0 = list2vec([one, one,   0,   0,   0, one])

def choose_secret_vector(s,t):
    u = [0, 0, 0, 0, 0, 0]
    u[1] = randGF2()
    u[2] = randGF2()
    u[4] = randGF2()
    u[5] = randGF2()
    u[0] = t - u[1] - u[5]
    u[3] = s - t 
    return list2vec(u) 
    
    
## 2: (Task 2) Finding Secret Sharing Vectors
# Give each vector as a Vec instance
def generate_vec(n):
    v = [0] * n
    for i in range(n):
        v[i] = randGF2()
    return list2vec(v)
    
def generate_secrets(a0, b0):
    # select 3 pairs from 5, they are all independent
    # select 4 pairs from 5, they are all not independent, this is certainly     
    n = len(a0.D)
    choose_3_from_5 = list(itertools.combinations(range(5), 3))
    count = 0
    while True:
        print(count)
        count += 1
        res = []
        a1, b1 = generate_vec(n), generate_vec(n)
        a2, b2 = generate_vec(n), generate_vec(n)
        a3, b3 = generate_vec(n), generate_vec(n)
        a4, b4 = generate_vec(n), generate_vec(n)
        res.append([a0, a1, a2, a3, a4])
        res.append([b0, b1, b2, b3, b4])
        fail_flag = False
        for choose in choose_3_from_5:
            chosen_vecs = set()
            for i in range(len(choose)):
                chosen_vecs.add(res[0][choose[i]])
                chosen_vecs.add(res[1][choose[i]])
            
            if len(chosen_vecs) != 6:
                print("p1");
                fail_flag = True
                break
        
            if not is_independent(chosen_vecs):
                print("p2")
                fail_flag = True
                break
        
        if not fail_flag:
            return res
        
secret_a0 = Vec({0, 1, 2, 3, 4, 5},{0: one, 1: one, 2: 0, 3: one, 4: 0, 5: one})
secret_b0 = Vec({0, 1, 2, 3, 4, 5},{0: one, 1: one, 2: 0, 3: 0, 4: 0, 5: one})
secret_a1 = Vec({0, 1, 2, 3, 4, 5},{0: 0, 1: one, 2: 0, 3: one, 4: one, 5: 0})
secret_b1 = Vec({0, 1, 2, 3, 4, 5},{0: one, 1: one, 2: one, 3: 0, 4: 0, 5: one})
secret_a2 = Vec({0, 1, 2, 3, 4, 5},{0: 0, 1: 0, 2: 0, 3: 0, 4: 0, 5: one})
secret_b2 = Vec({0, 1, 2, 3, 4, 5},{0: one, 1: one, 2: 0, 3: one, 4: one, 5: one})
secret_a3 = Vec({0, 1, 2, 3, 4, 5},{0: 0, 1: 0, 2: one, 3: 0, 4: 0, 5: one})
secret_b3 = Vec({0, 1, 2, 3, 4, 5},{0: one, 1: 0, 2: one, 3: one, 4: 0, 5: one})
secret_a4 = Vec({0, 1, 2, 3, 4, 5},{0: 0, 1: 0, 2: one, 3: 0, 4: one, 5: 0})
secret_b4 = Vec({0, 1, 2, 3, 4, 5},{0: one, 1: 0, 2: 0, 3: 0, 4: one, 5: 0})


