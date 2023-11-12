import csv
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.backends.backend_pdf import PdfPages

class Graph:

    def __init__(self):

        self.lens = np.array([])
        self.Radix = np.array([])
        self.Comb = np.array([])
        self.Shell = np.array([])
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

                self.Radix = np.append(self.Radix, float(values[1]))
                self.Comb = np.append(self.Comb, float(values[2]))
                self.Shell = np.append(self.Shell, float(values[3]))

                if len(values) == 5:
                    self.Str = np.append(self.Str, float(values[4]))
            
    def buildGraph(self, pdf: PdfPages):
    
        plt.grid()
        plt.xlabel("Размер, эл.")
        plt.ylabel("Время, мкс.")

        plt.plot(self.lens, self.Radix / 1000, color = "red", marker = "+", linestyle = "-")
        plt.plot(self.lens, self.Comb / 1000, color = "green", marker = ".", linestyle = ":")
        plt.plot(self.lens, self.Shell / 1000, color = "blue", marker = "*", linestyle = "-.")

        legend = ["Поразрядная сортировка",
                    "Сортировка расчёской",
                    "Сортировка Шелла"]

    
        plt.legend(legend)

        pdf.savefig()

        plt.close()

if __name__ == "__main__":

    files = ['time_even.csv',
             'time_odd.csv',
             'time_ext.csv']
    
    with PdfPages('../../report/img/figures.pdf') as pdf:
        
        for file in files:

            graph = Graph()
            graph.readFile(file)
            graph.buildGraph(pdf)
  