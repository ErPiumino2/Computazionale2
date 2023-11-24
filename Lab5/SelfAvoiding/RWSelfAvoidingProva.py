import matplotlib.pyplot as plt
import numpy as np

plt.figure(figsize=(10,10))
fig = plt.figure()
ax = fig.add_subplot(111)
x1, y1 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/SelfAvoiding.dat', usecols=(0, 1), unpack=True)
N1 = len(x1)
#Vari plot
ax.plot(x1, y1, color='skyblue', label=f'Random Walk {N1-1:.0f} steps',  zorder=-1)
#Initial Points plots
ax.scatter(x1[0], y1[0], color='red', label=f'Starting Point: ({x1[0]:.0f}, {y1[0]:.0f})',  zorder=1)
#Final Points plots
ax.scatter(x1[-1], y1[-1], color='darkslategrey', label=f'Final Point:  ({x1[-1]:.0f}, {y1[-1]:.0f})', zorder=1)
#Empty plots
ax.xaxis.set_ticks(1, 2, ..., len(x1))
ax.grid(True)
ax.legend()
plt.savefig("SelfAvoiding.png")
