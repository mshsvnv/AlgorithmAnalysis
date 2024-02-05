def choose_next_loc(self, P: np.array):
    
    posibility = r.random()
    cities = np.size(P)
    cur_posibility = 0
    to = 0

    while (cur_posibility < posibility) and (to < cities):
        cur_posibility += P[to]
        to += 1
    
    return to - 1