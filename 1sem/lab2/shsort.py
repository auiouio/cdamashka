import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import csv

colors_list = list(colors._colors_full_map.values())

times = []
swaps = []
N = []
file = open((r"C:\Users\auiod\cdamashka\cdamashka\lab2\shsort.csv"), "rt")
file_reader = csv.reader(file, delimiter = ",")
count = 0
for row in file_reader:

    print(row)
    times.append(row[0])
    N.append(row[1])
    #swaps.append(row[2])
    count += 1
print(f'Всего в файле {count} строк.')

file = open((r"C:\Users\auiod\cdamashka\cdamashka\lab2\shsort2.csv"), "rt")
file_reader = csv.reader(file, delimiter = ",")
count = 0
times2 = []
N2 = []
for row in file_reader:

    print(row)
    times2.append(row[0])
    N2.append(row[1])
    #swaps.append(row[2])
    count += 1
print(f'Всего в файле {count} строк.')

file = open((r"C:\Users\auiod\cdamashka\cdamashka\lab2\shsort3.csv"), "rt")
file_reader = csv.reader(file, delimiter = ",")
count = 0
times3 = []
N3 = []
for row in file_reader:

    print(row)
    times3.append(row[0])
    N3.append(row[1])
    #swaps.append(row[2])
    count += 1
print(f'Всего в файле {count} строк.')


plt.xlabel('N')
plt.ylabel('times')

'''N_fit = np.linspace(0, 10000)  
y_fit = []
a, b = np.polyfit(N, times, 1, cov=True)  
for N in N_fit:
    y_fit.append(X * a[0] + a[1])  '''
fig, ax = plt.subplots()
ax.plot(N, times, label = 'fb')



plt.plot(N, times, 'rs', color = colors_list[9])
plt.plot(N2, times2, 'rs', color = colors_list[4])
plt.plot(N3, times3, 'rs', color = colors_list[8])


#plt.plot(N_fit, y_fit)

plt.show()