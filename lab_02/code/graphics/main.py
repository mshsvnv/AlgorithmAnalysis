import csv
import matplotlib.pyplot as plt
import numpy as np
import re

class Graph:

    def __init__(self):

        self.lens = np.array([])
        self.Std = np.array([])
        self.Vin = np.array([])
        self.VinOpt = np.array([])
        self.Str = np.array([])

    def readFile(self, fileName):

        with open(fileName, 'r') as file:
            
            spamreader = csv.reader(file, delimiter=',', quotechar='|')
            i = 0
            for values in spamreader:
                
                if not i:
                    i += 1
                    continue

                self.lens = np.append(self.lens, int(values[0]))

                self.Std = np.append(self.Std, float(values[1]))
                self.Vin = np.append(self.Vin, float(values[2]))
                self.VinOpt = np.append(self.VinOpt, float(values[3]))

                if len(values) == 5:
                    self.Str = np.append(self.Str, float(values[4]))
            
    def buildGraph(self):
        
        plt.grid()
        plt.xlabel("Размер, эл.")
        plt.ylabel("Время, мкс.")

        plt.plot(self.lens, self.Std, color = "red", marker = "+", linestyle = "-")
        plt.plot(self.lens, self.Vin, color = "green", marker = ".", linestyle = ":")
        plt.plot(self.lens, self.VinOpt, color = "blue", marker = "*", linestyle = "-.")

        legend = ["Стандартный алгоритм умножения",
                    "Алгоритм Винограда",
                    "Оптимизированный алгоритм Винограда"]

        if len(self.Str):
            plt.plot(self.lens, self.Str, color = "magenta", marker = "h", linestyle = "--")
            legend.append("Алгоритм Штрассена")

        plt.legend(legend)

        plt.show()

if __name__ == "__main__":

    graph = Graph()
    graph.readFile('time_even.csv')
    graph.buildGraph()
  
    graph = Graph()
    graph.readFile('time_odd.csv')
    graph.buildGraph()

    graph = Graph()
    graph.readFile('time_ext.csv')
    graph.buildGraph()