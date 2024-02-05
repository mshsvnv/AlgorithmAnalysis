from defines import *
from test import *
import utils as u

def main():
    option = -1
    while option != EXIT:
        try:
            option = int(input(MSG))
        except ValueError:
            option = -1
        if (option == BRUTE_FORCE):
            u.run_brute_force()
        elif (option == ANT_ALG):
            u.run_ant_algorithm()
        elif (option == ALG_ALL):
            u.run_all()
        elif (option == PARAMETRIC):
            parametrization(type = CSV)
        elif (option == TEST):
            testTime()
        elif (option == UPDATE_DATA):
            u.update_file()
        elif (option == SHOW_DATA):
            u.print_matrix()
        elif (option == EXIT):
            continue
        else:
            print("Повторите ввод")

if __name__ == "__main__":
    main()

# import numpy as np
# import random as r

# alfa = 0.7    # к-ф запаха
# beta = 1 - alfa  # к-ф расстояния
# rho = 0.5  # к-ф высыхания
# Q = 1      # к-во выпускаемого ферромона
# days = 5   # кол-во дней

# all_ants = 2  # кол-во муравьев
# elite_ants = 5 # кол-во элитных муравьев

# cities = 4 # кол-во городов

# ph = Q / cities # начальное значение феромона

# # матрица смежности
# L = np.random.randint(1, 50, size = (cities, cities))
# rev_L = 1 / L

# for i in range(cities):
#     L[i, i] = 0

# print(L)

# # матрица феромонов
# tao = np.ones((cities, cities)) * ph

# ant_routes = np.zeros((all_ants, cities))    # матрица путей
# ant_dist = np.zeros((all_ants))              # вектор расстояний
# ant_best_dist = np.zeros(days)               # вектор лучших расстояний за каждый день

# best_route = None                            # лучший маршрут
# best_dist = float("inf")                     # лучшая длина

# for day in range(days):

#     # print(f"День: {day + 1}")
#     # print(tao)

#     ant_dist.fill(0)
#     ant_routes.fill(0)
    
#     for ant in range(all_ants):
        
#         ant_routes[ant, 0] = r.randint(0, cities - 1)
        
#         for i in range(1, cities):

#             from_city = int(ant_routes[ant, i - 1])
            
#             # вероятность перехода в новый город
#             P = (rev_L[from_city] ** beta) * (tao[from_city] ** alfa)

#             for j in range(i):
#                 P[int(ant_routes[ant, j])] = 0
            
#             P = P / np.sum(P)
            
#             # выбор нового города
#             posibility = r.random()
#             cur_posipility = 0
#             to = 0

#             while (cur_posipility < posibility) and (to < cities):
#                 cur_posipility += P[to]
#                 to += 1

#             ant_routes[ant, i] = to - 1
        
#         # расчет длины пути
#         for i in range(cities - 1):
#             city_from = int(ant_routes[ant, i])
#             city_to = int(ant_routes[ant, i + 1])

#             ant_dist[ant] += L[city_from, city_to]

#         # обновляем самый короткий путь
#         if ant_dist[ant] < best_dist:
#             best_dist = ant_dist[ant]
#             best_route = np.copy(ant_routes[ant])

#     # обновляем феромон
#     tao *= rho

#     for ant in range(all_ants):
#         delta_tao = Q / ant_dist[ant]

#         cur_route = ant_routes[ant]

#         for i in range(cities - 1):
#             city_from = int(cur_route[i])
#             city_to = int(cur_route[i + 1])

#             tao[city_from, city_to] += delta_tao
#             tao[city_to, city_from] += delta_tao

#     # элитные муравьи
#     delta_tao =  elite_ants * Q / best_dist

#     for city in range(cities - 1):
#         city_from = int(best_route[i])
#         city_to = int(best_route[i + 1])

#         tao[city_from, city_to] += delta_tao
#         tao[city_to, city_from] += delta_tao
        
#     # print(ant_dist, ant_routes)

# from itertools import permutations
# perms = list(permutations(list(range(cities))))

# best = float("inf")
# route = None

# for perm in perms:

#     cur_dist = 0

#     for i in range(cities - 1):
#         cur_dist += L[perm[i], perm[i + 1]]
    
#     if best > cur_dist:
#         best = cur_dist
#         route = perm

# print(best, route)
# print(best_dist, best_route)











