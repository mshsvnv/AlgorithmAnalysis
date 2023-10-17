import csv
import matplotlib.pyplot as plt
import numpy as np

def readFile(fileName):

    with open(fileName, 'r') as file:
        csv_reader = csv.reader(file)

        lens = []
        lev = []
        dam_lev = []
        rec = []
        rec_cash = []

        i = 0

        for row in csv_reader:
            i += 1

            if i == 1:
                continue
            else:
                row = list(map(int, row))

                lens.append(row[0])
                lev.append(row[1])
                dam_lev.append(row[2])
                rec.append(row[3])
                rec_cash.append(row[4])

def buildRecursive():
    
    plt.grid()
    plt.xlabel("Длина, симв.")
    plt.ylabel("Время, нс.")

    plt.plot(lens[:11], rec[:11], color = "red", marker = "+", linestyle = "-")
    plt.plot(lens[:11], rec_cash[:11], color = "green", marker = ".", linestyle = ":")


    plt.legend(["Рекурсивный Дамерау-Левенштейн",
                "Рекурсивный Дамерау-Левенштейн с кешем"])

    plt.show()

def buildNonRecursive():
    
    plt.grid()
    plt.xlabel("Длина, симв.")
    plt.ylabel("Время, нс.")

    plt.plot(lens, lev, color = "magenta", marker = "+", linestyle = "-")
    plt.plot(lens, dam_lev, color = "blue", marker = ".", linestyle = ":")

    plt.legend(["Нерекурсивный Левенштейн", 
                "Нерекурсивный Дамерау-Левенштейн"])
    
    plt.show()

def buildExtra():

    plt.grid()
    plt.xlabel("Длина, симв.")
    plt.ylabel("Время, нс.")

    plt.plot(lens[:11], lev[:11], color = "magenta", marker = "+", linestyle = "-")
    plt.plot(lens[:11], dam_lev[:11], color = "blue", marker = ".", linestyle = "-.")

    plt.plot(lens[:11], rec_cash[:11], color = "green", marker = "2")

    plt.legend(["Нерекурсивный Левенштейн", 
                "Нерекурсивный Дамерау-Левенштейн",
                "Рекурсивный Дамерау-Левенштейн с кешем"])

    plt.show()

with open('time.csv', 'r') as file:
    csv_reader = csv.reader(file)

    headers = []
    lens = []
    lev = []
    dam_lev = []
    rec = []
    rec_cash = []

    i = 0

    for row in csv_reader:
        i += 1

        if i == 1:
            continue
        else:
            lens.append(int(row[0]))
            lev.append(float(row[1]))
            dam_lev.append(float(row[2]))
            rec.append(float(row[3]))
            rec_cash.append(float(row[4]))

if __name__ == "__main__":

    readFile('time.csv')
    buildRecursive()
    buildNonRecursive()
    buildExtra()
