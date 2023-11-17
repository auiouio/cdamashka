import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import csv

colors_list = list(colors._colors_full_map.values())

times = []
swaps = []
N = []
#file  = open(r("C:\Users\auiod\OneDrive\Рабочий стол\sort.csv"), "rt", encoding='theencodingofthefile')
file = open((r"C:\Users\auiod\OneDrive\Рабочий стол\sort.csv"), "rt")
# Создаем объект reader, указываем символ-разделитель ","
file_reader = csv.reader(file, delimiter = ",")
# Счетчик для подсчета количества строк и вывода заголовков столбцов
count = 0
# Считывание данных из CSV файла
for row in file_reader:
    '''row[0] = int( row[0])
    row[1] = int(row[1])
    row[2] = int(row[2])'''
    print(row)
    times.append(row[1])
    N.append(row[0])
    swaps.append(row[2])
    print(f'    {row[0]} - {row[1]} и он родился в {row[2]} году.')
    count += 1
print(f'Всего в файле {count} строк.')


plt.xlabel('N')
plt.ylabel('times')

'''N_fit = np.linspace(0, 10000)  # иксы точек, которые мы аппроксисируем, просто много точек в нужном диапазоне
y_fit = []
a, b = np.polyfit(N, times, 1, cov=True)  # 2- степень многочлена, a- массив коэфф. многочлена начиная с большего, cov = true
# чтобы вывело b- матрицу погрешностей, в ней по диагонали погрешности коэффициентов
for N in N_fit:
    y_fit.append(X * a[0] + a[1])  # расписываем многочлен'''



'''sigma_A = b[0][0]  # Погрешности A, B, C
sigma_B = b[1][1]'''


plt.plot(N, times, 'rs', color = colors_list[9])
#plt.plot(N_fit, y_fit)

plt.show()