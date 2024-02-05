import random as r

def gen_mat(st, end, size):
    mat = [[r.randint(st, end) for _ in range(size)] for _ in range(size)]
    for i in range(size):
        mat[i][i] = 0
    return mat

with open('data/param_low_diff.csv', 'w', encoding='utf-8') as f:
    mat = gen_mat(1, 2, 9)
    for i in range(len(mat)):
        print(*mat[i], sep=',', file=f)
        
with open('data/param_high_diff.csv', 'w', encoding='utf-8') as f:
    mat = gen_mat(1, 9999, 9)
    for i in range(len(mat)):
        print(*mat[i], sep=',', file=f)