import csv
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.backends.backend_pdf import PdfPages

class Graph:

    def __init__(self):

        self.lens = np.array([])
        self.merge = np.array([])
        self.mergeTh = np.array([])
        self.amount = np.array([])

    def readFile(self, fileName):

        with open(fileName, 'r') as file:
            
            spamreader = csv.reader(file, delimiter=',', quotechar='|')
            i = 0
            for values in spamreader:
                
                if not i:
                    i += 1
                    continue

                self.lens = np.append(self.lens, int(values[0]))

                self.merge = np.append(self.merge, float(values[1]))
                self.mergeTh = np.append(self.mergeTh, float(values[2]))
                self.amount = np.append(self.amount, float(values[3]))

    def buildGraphAm(self, pdf: PdfPages):
        
        plt.grid()
        plt.xlabel("Кол-во элементов")

        plt.ylabel("Время, мс.")

        plt.plot(self.lens, self.merge, color = "red", marker = "+", linestyle = "-")
        plt.plot(self.lens, self.mergeTh, color = "blue", marker = "*")
        
        legend = ["Использование одного потока",
                  "Использование одного дополнительного потока"]

        plt.legend(legend)
        pdf.savefig()
        plt.close()
    
    def buildGraphTh(self, pdf: PdfPages):
    
        plt.grid()
        plt.xlabel("Кол-во потоков")

        plt.ylabel("Время, мс.")

        plt.plot(self.amount, self.merge, color = "red", marker = "+", linestyle = "-")
        plt.plot(self.amount, self.mergeTh, color = "blue", marker = "*")
        
        legend = ["Использование одного потока",
                  "Использование нескольких потоков"]

        plt.legend(legend)
        pdf.savefig()
        plt.close()

if __name__ == "__main__":

    files = ['time_amount.csv',
             'time_threads.csv']
    
    i = 0
    
    with PdfPages('../report/inc/figures.pdf') as pdf:
        
        for file in files:
            
            graph = Graph()
            graph.readFile(file)

            if i == 0:
                graph.buildGraphAm(pdf) 
            else:
                graph.buildGraphTh(pdf)

            i += 1
  