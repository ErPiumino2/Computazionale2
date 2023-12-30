import matplotlib.pyplot as plt
import numpy as np

fig, ax = plt.subplots(3,2)
fig.set_figwidth(20)
fig.set_figheight(20)
fig.suptitle('Histograms of final position of 1000 Random Walk for various number of steps', fontsize=20)
x1, y1 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW2DHiston=10.dat', usecols=(0, 1), unpack=True)
x2, y2 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW2DHiston=60.dat', usecols=(0, 1), unpack=True)
x3, y3 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW2DHiston=360.dat', usecols=(0, 1), unpack=True)
x4, y4 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW2DHiston=2160.dat', usecols=(0, 1), unpack=True)
x5, y5 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW2DHiston=12960.dat', usecols=(0, 1), unpack=True)
x6, y6 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW2DHiston=77760.dat', usecols=(0, 1), unpack=True)
# Calcola i valori minimo e massimo dei dati
data1x_min = np.min(x1)
data1y_min = np.min(y1)
data1x_max = np.max(x1)
data1y_max = np.max(y1)
data2x_min = np.min(x2)
data2y_min = np.min(y2)
data2x_max = np.max(x2)
data2y_max = np.max(y2)
data3x_min = np.min(x3)
data3y_min = np.min(y3)
data3x_max = np.max(x3)
data3y_max = np.max(y3)
data4x_min = np.min(x4)
data4y_min = np.min(y4)
data4x_max = np.max(x4)
data4y_max = np.max(y4)
data5x_min = np.min(x5)
data5y_min = np.min(y5)
data5x_max = np.max(x5)
data5y_max = np.max(y5)
data6x_min = np.min(x6)
data6y_min = np.min(y6)
data6x_max = np.max(x6)
data6y_max = np.max(y6)
# Calcola il numero di bin desiderato (uno per uno)
num_bins1x = int(data1x_max - data1x_min + 1)
num_bins1y = int(data1y_max - data1y_min + 1)
num_bins2x = int(data2x_max - data2x_min + 1)
num_bins2y = int(data2y_max - data2y_min + 1)
num_bins3x = int(data3x_max - data3x_min + 1)
num_bins3y = int(data3y_max - data3y_min + 1)
num_bins4x = int(data4x_max - data4x_min + 1)
num_bins4y = int(data4y_max - data4y_min + 1)
num_bins5x = int(data5x_max - data5x_min + 1)
num_bins5y = int(data5y_max - data5y_min + 1)
num_bins6x = int(data6x_max - data6x_min + 1)
num_bins6y = int(data6y_max - data6y_min + 1)
# Crea l'istogramma
a1, b1, c1 = ax[0,0].hist(x1, bins=num_bins1x, range=(data1x_min, data1x_max+1), color='red', alpha=0.6, label='x data')
d1, e1, f1 = ax[0,0].hist(y1, bins=num_bins1y, range=(data1y_min, data1y_max+1), color='skyblue', alpha=0.6, label='y data')
a2, b2, c2 = ax[0,1].hist(x2, bins=num_bins2x, range=(data2x_min, data2x_max+1), color='red', alpha=0.6, label='x data')
d2, e2, f2 = ax[0,1].hist(y2, bins=num_bins2y, range=(data2y_min, data2y_max+1), color='skyblue', alpha=0.6, label='y data')
a3, b3, c3 = ax[1,0].hist(x3, bins=num_bins3x, range=(data3x_min, data3x_max+1), color='red', alpha=0.6, label='x data')
d3, e3, f3 = ax[1,0].hist(y3, bins=num_bins3y, range=(data3y_min, data3y_max+1), color='skyblue', alpha=0.6, label='y data')
a4, b4, c4 = ax[1,1].hist(x4, bins=num_bins4x, range=(data4x_min, data4x_max+1), color='red', alpha=0.6, label='x data')
d4, e4, f4 = ax[1,1].hist(y4, bins=num_bins4y, range=(data4y_min, data4y_max+1), color='skyblue', alpha=0.6, label='y data')
a5, b5, c5 = ax[2,0].hist(x5, bins=num_bins5x, range=(data5x_min, data5x_max+1), color='red', alpha=0.6, label='x data')
d5, e5, f5 = ax[2,0].hist(y5, bins=num_bins5y, range=(data5y_min, data5y_max+1), color='skyblue', alpha=0.6, label='y data')
a6, b6, c6 = ax[2,1].hist(x6, bins=num_bins6x, range=(data6x_min, data6x_max+1), color='red', alpha=0.6, label='x data')
d6, e6, f6 = ax[2,1].hist(y6, bins=num_bins6y, range=(data6y_min, data6y_max+1), color='skyblue', alpha=0.6, label='y data')

ax[0,0].plot([], [], '', label='Steps=10', alpha=0)
ax[0,1].plot([], [], '', label='Steps=60', alpha=0)
ax[1,0].plot([], [], '', label='Steps=360', alpha=0)
ax[1,1].plot([], [], '', label='Steps=2160', alpha=0)
ax[2,0].plot([], [], '', label='Steps=12960', alpha=0)
ax[2,1].plot([], [], '', label='Steps=77760', alpha=0)

for ax in ax.flat:
    ax.set(xlabel='Occurrences', ylabel='Frequency')
    ax.legend()
plt.savefig('Istogrammi.png')