import os
import numpy as np
import pandas as pd
from random import randint
from ants import *
from brute_force import brute_force

def gen_matrix(size, start, end):
    matrix = np.zeros((size, size))

    for i in range(size):
        for j in range(size):
            if i == j:
                num = 0
            else:
                num = randint(start, end)
            matrix[i][j] = num
            matrix[j][i] = num
    return matrix


def gen_matrix_file(filename, size, start, end):
    matrix = gen_matrix(size, start, end)
    np.savetxt(filename, matrix, fmt="%.2f")


def read_matrix_from_file(filename: str):
    if filename.endswith(".txt"):
        return np.loadtxt(filename)
    else:
        return pd.read_csv(filename, delimiter=",", header=None).values


def list_datasets(directory="data"):
    all_files = [
        os.path.abspath(os.path.join(directory, f))
        for f in os.listdir(directory)
        if os.path.isfile(os.path.join(directory, f))
    ]
    print("Доступные датасеты:")
    for n, f in enumerate(all_files, start=1):
        filename = os.path.basename(f)
        print(f"    {n}. {filename}")
    return all_files


def update_file():
    try:
        option = int(input("\nДобавить новый файл? (1 - да, 2 - нет): "))
        if option == 1:
            file_name = input("\nВведите имя файла: ")
            size = int(input("\nВведите размер матрицы: "))
            rand_start = int(input("\nВведите начальное число рандома: "))
            rand_end = int(input("\nВведите конечное число рандома: "))
            print(gen_matrix_file(file_name, size, rand_start, rand_end))
        elif option == 2:
            files = list_datasets()
            num_file = int(input("\nВыберите файл: ")) - 1
            size = int(input("\nВведите размер матрицы: "))
            rand_start = int(input("\nВведите начальное число рандома: "))
            rand_end = int(input("\nВведите конечное число рандома: "))
            print(gen_matrix_file(files[num_file], size, rand_start, rand_end))
        else:
            print("\nОшибка: Неверно выбран пункт")
        print("\n\nУспешно обновлен список файлов\n")
    except:
        print("\nОшибка: Неверно выбран пункт")


def print_matrix():
    files = list_datasets()
    try:
        ifile = int(input("\nВыберите файл: ")) - 1
    except:
        print("Неверно выбран файл\n")
        return
    matrix = read_matrix_from_file(files[ifile])
    print(matrix)
    print()


def read_matrix():
    files = list_datasets()
    fileIndex = int(input("\nВыберите файл: ")) - 1
    matrix = read_matrix_from_file(files[fileIndex])
    return matrix


def run_brute_force():
    matrix = read_matrix()
    size = len(matrix)
    result = brute_force(matrix, size)
    print("\n\nМинимальная сумма пути = ", result[0], "\nПуть: ", result[1])

def get_coefficients():
    try:
        a = float(input("    Введите коэффициент alpha: "))
        b = 1 - a
        rho = float(input("    Введите коэффициент испарения: "))
        days = int(input("    Введите кол-во дней: "))
        elite = int(input("    Введите количество элитных муравьев: "))
    except:
        print("    Введены недопустимые значения. Используются значения по умолчанию")
    a = 0
    b = 1
    rho = 0.5
    days = 180
    elite = 5

    return a, b, rho, days, elite

def run_ant_algorithm():
    matrix = read_matrix()
    size = len(matrix)

    alg = AntAlgorithm(*get_coefficients())

    result = alg.fit(matrix, size)
    print("\n\nМинимальная длина пути =", result[0], "\nПуть: ", result[1])

def run_all():
    matrix = read_matrix()
    size = len(matrix)

    result = brute_force(matrix, size)

    print(
        "\n\nАлгоритм полного перебора \
            \n\tМинимальная длина пути =",
        result[0],
        "\n\tПуть: ",
        result[1],
    )

    alg = AntAlgorithm(*get_coefficients())

    result = alg.fit(matrix, size)

    print(
        "\n\nМуравьиный алгоритм \
            \n\tМинимальная длина пути =",
        result[0],
        "\n\tПуть: ",
        result[1],
    )