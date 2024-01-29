import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('times.csv')

x = df['size']
y1 = df['l']
y2 = df['p']

plt.plot(x, y1, label = 'Последовательный', color='red', linestyle='--', marker = '*')
plt.plot(x, y2, label = 'Параллельный', color='blue', linestyle='-', marker = 's')

plt.xlabel('Количество заявок (ед.)')
plt.ylabel('Время (мкс.)')

plt.legend()

plt.grid()
plt.show()