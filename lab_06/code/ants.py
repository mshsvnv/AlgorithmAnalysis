import numpy as np
import random as r

from defines import *

class AntAlgorithm:

    def __init__(
            self,
            a,
            b,
            rho,
            days,
            elite = 0):
        self.a = a
        self.b = b
        self.rho = rho
        self.days = days 
        self.elite = elite
        self.Q = None
    
    def calc_q(self, L: np.ndarray):
        return np.sum(L) / np.size(L)
    
    def choose_next_loc(self, P: np.array):
        posibility = r.random()
        cities = np.size(P)
        cur_posibility = 0
        to = 0

        while (cur_posibility < posibility) and (to < cities):
            cur_posibility += P[to]
            to += 1
        
        return to - 1
    
    def calc_len(self, L: np.ndarray, ant_route):

        cities = np.size(L[0])
        ant_dist = 0

        for i in range(cities - 1):
            city_from = int(ant_route[i])
            city_to = int(ant_route[i + 1])

            ant_dist += L[city_from, city_to]
        
        return ant_dist
    
    def update_pher_elite(self, tao: np.ndarray, best_dist: float, best_route: np.array):
        
        cities = np.size(tao[0])
        delta_tao =  self.elite * self.Q / best_dist

        for i in range(cities - 1):
            city_from = int(best_route[i])
            city_to = int(best_route[i + 1])

            tao[city_from, city_to] += delta_tao
            tao[city_to, city_from] += delta_tao

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