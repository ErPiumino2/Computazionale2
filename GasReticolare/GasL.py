import matplotlib.pyplot as plt
import numpy as np

x_holder = {}
y_holder = {}
L = 20
markers = ['x', '.', '^', 'D']

fig = plt.figure(figsize=(15, 12), dpi=80)
plt.title("Behaviour of average movement for different values of L", fontsize=15)
for i in range(1,5):
    x_holder['x' + str(i)], y_holder['y' + str(i)] = np.loadtxt(f"/workspaces/Computazionale2/GasReticolare/File/A(t)L={L*i}ro=0.60.dat", usecols=(0,1), unpack=True)
    plt.scatter(x_holder['x'+ str(i)], y_holder['y' + str(i)], marker=markers[i-1], s=35, label=f'$L={L*i}$')
locals().update(x_holder)
locals().update(y_holder)
plt.plot([], [], '', label='$\\rho = 0.60$', alpha=0)
plt.plot([], [], '', label='Number of simulation = 1000', alpha=0)
plt.legend(fontsize=15)
plt.xlabel('Moves', fontsize=15)
plt.ylabel('A(t)', fontsize=15)
plt.ylim(0.077, 0.079)
plt.savefig("GasL1000.png")