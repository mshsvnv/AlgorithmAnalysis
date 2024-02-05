def brute_force(matrix, size):

    perms = list(permutations(list(range(size))))

    best_dist = float("inf")
    best_route = None

    for perm in perms:

        cur_dist = 0

        for i in range(size - 1):
            cur_dist += matrix[perm[i], perm[i + 1]]
        
        if best_dist > cur_dist:
            best_dist = cur_dist
            best_route = perm

    return int(best_dist), best_route