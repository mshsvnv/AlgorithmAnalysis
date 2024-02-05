def fit(
            self,
            L,
            ANTS):

        cities = np.size(L[0])

        rev_L = np.zeros((cities, cities))
        for i in range(cities):
            for j in range(cities):
                if L[i, j] != 0:
                    rev_L[i, j] = 1 / L[i, j]
        
        self.Q = self.calc_q(L)

        ph = self.Q / cities
    
        # матрица феромонов
        tao = np.ones((cities, cities)) * ph

        ant_routes = np.zeros((ANTS, cities))    # матрица путей
        ant_dist = np.zeros((ANTS))              # вектор расстояний

        best_route = None                        # лучший маршрут
        best_dist = float("inf")                 # лучшая длина

        for day in range(self.days):

            ant_dist.fill(0)
            ant_routes.fill(0)
            
            for ant in range(ANTS):
                
                ant_routes[ant, 0] = r.randint(0, cities - 1)
                
                for i in range(1, cities):

                    from_city = int(ant_routes[ant, i - 1])
                    
                    # вероятность перехода в новый город
                    P = (rev_L[from_city] ** self.b) * (tao[from_city] ** self.a)

                    for j in range(i):
                        P[int(ant_routes[ant, j])] = 0
                    
                    P = P / np.sum(P)
                    
                    # выбор нового города
                    ant_routes[ant, i] = self.choose_next_loc(P)
                
                # расчет длины пути
                ant_dist[ant] = self.calc_len(L, ant_routes[ant])

                # обновляем самый короткий путь
                if ant_dist[ant] < best_dist:
                    best_dist = ant_dist[ant]
                    best_route = np.copy(ant_routes[ant])

            # обновляем феромон
            tao *= self.rho

            for ant in range(ANTS):
                delta_tao = self.Q / ant_dist[ant]

                cur_route = ant_routes[ant]

                for i in range(cities - 1):
                    city_from = int(cur_route[i])
                    city_to = int(cur_route[i + 1])

                    tao[city_from, city_to] += delta_tao
                    tao[city_to, city_from] += delta_tao

                    if tao[city_from, city_to] < MIN_PHER:
                        tao[city_from, city_to] = MIN_PHER
                        tao[city_to, city_from, ] = MIN_PHER

            # элитные муравьи
            self.update_pher_elite(tao, best_dist, best_route)

        return best_dist, best_route