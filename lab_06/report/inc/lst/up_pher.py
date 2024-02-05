def update_pher_elite(self, tao: np.ndarray, best_dist: float, best_route: np.array):
        
        cities = np.size(tao[0])
        delta_tao =  self.elite * self.Q / best_dist

        for i in range(cities - 1):
            city_from = int(best_route[i])
            city_to = int(best_route[i + 1])

            tao[city_from, city_to] += delta_tao
            tao[city_to, city_from] += delta_tao