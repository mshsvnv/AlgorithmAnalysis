import csv
import matplotlib.pyplot as plt
import numpy as np
import re

class Graph:

    def __init__(self):

        self.lens = np.array([])
        self.Lev = np.array([])
        self.DamLev = np.array([])
        self.Rec = np.array([])
        self.RecCash = np.array([])

    def readFile(self, fileName):

        with open(fileName, 'r') as file:
            
            for line in file:

                values = re.findall(r'\b\d+\.?\d*\b', line)

                self.lens = np.append(self.lens, int(values[0]))

                self.Lev = np.append(self.Lev, float(values[1]))
                self.DamLev = np.append(self.DamLev, float(values[2]))
            
                if self.lens[-1] >= 20:
                    self.RecCash = np.append(self.RecCash, float(values[3]))
                else:
                    self.Rec = np.append(self.Rec, float(values[3]))
                    self.RecCash = np.append(self.RecCash, float(values[4]))

    def buildRecursive(self):
        
        plt.grid()
        plt.xlabel("Длина, симв.")
        plt.ylabel("Время, мкс.")

        plt.plot(self.lens[:11], self.Rec / 1000, color = "red", marker = "+", linestyle = "-")
        plt.plot(self.lens[:11], self.RecCash[:11] / 1000, color = "green", marker = ".", linestyle = ":")

        plt.legend(["Рекурсивный Дамерау-Левенштейн",
                    "Рекурсивный Дамерау-Левенштейн с кешем"])
        
        # plt.semilogx()
        plt.semilogy()

        plt.show()

    def buildNonRecursive(self):
        
        plt.grid()
        plt.xlabel("Длина, симв.")
        plt.ylabel("Время, мкс.")

        plt.plot(self.lens, self.Lev / 1000, color = "magenta", marker = "+", linestyle = "-")
        plt.plot(self.lens, self.DamLev / 1000, color = "blue", marker = ".", linestyle = ":")

        plt.legend(["Нерекурсивный Левенштейн", 
                    "Нерекурсивный Дамерау-Левенштейн"])
        
        plt.show()

    def buildExtra(self):

        plt.grid()
        plt.xlabel("Длина, симв.")
        plt.ylabel("Время, мкс.")

        plt.plot(self.lens, self.DamLev / 1000, color = "blue", marker = ".", linestyle = "-.")
        plt.plot(self.lens, self.RecCash / 1000, color = "green", marker = "2")

        plt.legend(["Нерекурсивный Дамерау-Левенштейн",
                    "Рекурсивный Дамерау-Левенштейн с кешем"])

        plt.show()

if __name__ == "__main__":

    graph = Graph()

    graph.readFile('time.txt')
    graph.buildRecursive()
    graph.buildNonRecursive()
    graph.buildExtra()