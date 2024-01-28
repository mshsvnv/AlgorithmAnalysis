import csv
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.backends.backend_pdf import PdfPages

class Graph:

    def __init__(self):

        self.strr = np.array([])
        self.under_str = np.array([])
        self.values = np.array( np.array([]) )

    def readFile(self, fileName):

        with open(fileName, 'r') as file:
            
            spamreader = csv.reader(file, delimiter=',', quotechar='|')
            i = -1
            for values in spamreader:
                
                i += 1
                if not i:
                    continue

                self.strr = np.append(self.strr, int(values[0]))

                self.under_str = np.append(self.under_str , float(values[1]))

                self.values = np.append(self.values, np.array([list(map(float, values[2:5]))]))
                
                # self.values[i] = np.append(self.values[i], float(values[2]))
                # self.values[i] = np.append(self.values[i], float(values[3]))
                # self.values[i] = np.append(self.values[i], float(values[4]))

def buildGraph(graph: Graph, graphMod: Graph, pdf: PdfPages, i):

    plt.grid()
    plt.xlabel("Длина строки, эл.")

    plt.ylabel("Кол-во сравнений")
    plt.semilogy()

    plt.plot(graph.strr, graph.values[:, i], color = "red", marker = "+", linestyle = "-")
    plt.plot(graph.strr, graphMod.values[:, i], color = "green", marker = ".", linestyle = ":")

    legend = ["Кнут-Моррис-Пратт",
              "Модифицированный КМП"]

    plt.legend(legend)
    plt.show()
    pdf.savefig()
    plt.close()

if __name__ == "__main__":

    files = ['../../report/inc/img/fig_best.pdf',
             '../../report/inc/img/fig_wosrt1.pdf',
             '../../report/inc/img/fig_wosrt2.pdf']
    
    graphKmp = Graph()
    graphKmp.readFile('time_kmp.csv')

    graphKmpMod = Graph()
    graphKmpMod.readFile('time_kmp_mod.csv')

    print(graphKmp.values[0, 0])

    # for i in range(3):
    #     buildGraph(graphKmp, graphKmpMod, PdfPages(files[i]), i)  