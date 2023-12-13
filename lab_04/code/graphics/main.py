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

    def buildGraph(self, pdf: PdfPages, type = 'time'):
    
        plt.grid()
        plt.xlabel("Размер, эл.")

        if (type == 'memory'):
            plt.ylabel("Объем, байт")
            plt.semilogy()
        else:
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

    files = ['time_asc.csv',
             'time_des.csv',
             'time_rand.csv',
             'memory.csv']
    
    i = 0
    
    with PdfPages('../../report/img/figures.pdf') as pdf:
        
        for file in files:
            
            graph = Graph()
            graph.readFile(file)

            if i == 3:
                graph.buildGraph(pdf, 'memory') 
            else:
                graph.buildGraph(pdf)

            i += 1
  