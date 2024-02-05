from utils import gen_matrix, read_matrix_from_file
from defines import CSV, LATEX
from time import process_time
from brute_force import brute_force
from ants import *
import matplotlib.pyplot as plt

def testTime():
    try:
        sizeStart = int(input("\n\nВведите начальный размер матрицы: "))
        sizeEnd = int(input("Введите конечный размер матрицы: "))
        if (sizeStart > sizeEnd or sizeStart < 0 or sizeEnd < 0):
            raise Exception
    except:
        print("Неправильные размеры матрицы!")
        return
    timeFullCombinations = []
    timeAntAlg = []
    sizes = [i for i in range(sizeStart, sizeEnd + 1)]
    count = 0
    print()

    for size in sizes:
        count += 1
        matrix = gen_matrix(size, 1, 2)

        start = process_time()
        brute_force(matrix, size)
        end = process_time()
        timeFullCombinations.append(end - start)

        start = process_time()
        alg = AntAlgorithm(0.5, 0.5, 0.5, 250)
        alg.fit(matrix, size)
        end = process_time()

        timeAntAlg.append(end - start)

        print("Progress: %3d%s" %((count / len(sizes)) * 100, "%"))

    # Table
    print("\n %s | %s | %s" %("Размер", "Время полного перебора", "Время муравьиного алгоритма"))
    print("-" * (8 + 1 + 24 + 1 + 29))

    for i in range(len(sizes)):
        print(" %6d | %22.6f | %27.6f" %(sizes[i], timeFullCombinations[i], timeAntAlg[i]))

    # For Latex
    f_latex = open("latex_table.txt", "w")

    for i in range(len(sizes)):
        f_latex.write("%4d & %10.6f & %10.6f \\\\ \\hline\n" %(sizes[i], timeFullCombinations[i], timeAntAlg[i]))

    f_latex.close()

    # Graph
    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(sizes, timeFullCombinations, linestyle='--', marker='*', markersize=10, label = "Полный перебор")
    plot.plot(sizes, timeAntAlg, marker='o', markersize=10, label="Муравьиный алгоритм")
    plt.yscale('log')
    plt.legend()
    plt.grid()
    plt.title("Временные характеристики")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Размер матрицы")

    plt.show()

def parametrization(type = CSV):
    alpha_arr = [num / 10 for num in range(1, 10)]
    rho_arr = [num / 10 for num in range(1, 9)]
    days_arr = [1, 3, 5, 10, 50, 100, 300, 500]

    size = 9

    matrix1 = read_matrix_from_file("data/param_low_diff.csv")
    matrix2 = read_matrix_from_file("data/param_high_diff.csv")

    optimal1 = brute_force(matrix1, size)
    optimal2 = brute_force(matrix2, size)

    file1 = open("params/param_class1.txt", "w")
    file2 = open("params/param_class2.txt", "w")

    count = 0
    count_all = len(alpha_arr) * len(rho_arr)

    for alpha in alpha_arr:
        beta = 1 - alpha
        for rho in rho_arr:
            count += 1
            for days in days_arr:
                alg = AntAlgorithm(alpha, beta, rho, days, 2)
                res1 = alg.fit(matrix1, size)
                res2 = alg.fit(matrix2, size)
                
                if (type == LATEX):
                    sep = " & "
                    ender = " \\\\"
                elif (type == CSV):
                    sep = ", "
                    ender = ""
                else:
                    sep = " | "
                    ender = ""

                str1 = "%4.1f%s%4.1f%s%4d%s%5d%s%5d%s\n" \
                    % (alpha, sep, rho, sep, days, sep, optimal1[0], sep, res1[0] - optimal1[0], ender)

                str2 = "%4.1f%s%4.1f%s%4d%s%5d%s%5d%s\n" \
                    % (alpha, sep, rho, sep, days, sep, optimal2[0], sep, res2[0] - optimal2[0], ender)

                file1.write(str1)
                file2.write(str2)

            print("Progress: %3d%s" %((count / count_all) * 100, "%"))

    file1.close()
    file2.close()