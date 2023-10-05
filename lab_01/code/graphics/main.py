import csv
import matplotlib.pyplot as plt

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
            row = list(map(int, row))

            lens.append(row[0])
            lev.append(row[1])
            dam_lev.append(row[2])
            rec.append(row[3])
            rec_cash.append(row[4])

    plt.grid()
    plt.xlabel("Длина, симв.")
    plt.ylabel("Время, нс.")

    plt.plot(lens, lev, color = "magenta", marker = "+", linestyle = "-")
    plt.plot(lens, dam_lev, color = "blue", marker = ".", linestyle = ":")

    plt.legend(["Нерекурсивный Левенштейн", 
                "Нерекурсивный Дамерау-Левенштейн"])
    
    plt.show()

    plt.grid()
    plt.xlabel("Длина, симв.")
    plt.ylabel("Время, нс.")

    plt.plot(lens[:11], rec[:11], color = "red", marker = "+", linestyle = "-")
    plt.plot(lens[:11], rec_cash[:11], color = "green", marker = ".", linestyle = ":")


    plt.legend(["Рекурсивный Дамерау-Левенштейн",
                "Рекурсивный Дамерау-Левенштейн с кешом"])

    plt.show()

    plt.grid()
    plt.xlabel("Длина, симв.")
    plt.ylabel("Время, нс.")

    plt.plot(lens, lev, color = "magenta", marker = "+", linestyle = "-")
    plt.plot(lens, dam_lev, color = "blue", marker = ".", linestyle = "-.")

    plt.plot(lens[:11], rec[:11], color = "red", marker = "1", linestyle = "-")
    plt.plot(lens[:11], rec_cash[:11], color = "green", marker = "2")

    plt.legend(["Нерекурсивный Левенштейн", 
                "Нерекурсивный Дамерау-Левенштейн",
                "Рекурсивный Дамерау-Левенштейн",
                "Рекурсивный Дамерау-Левенштейн с кешом"])

    plt.show()
