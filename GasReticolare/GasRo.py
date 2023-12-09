import matplotlib.pyplot as plt
import numpy as np

x_holder = {}
y_holder = {}
ro = 0.10
markers = ['x', '.', '^', 'D', 'd', 'x', '.', '^', 'D', 'd']

fig = plt.figure(figsize=(15, 12), dpi=80)
plt.title("Behaviour of average movement of particle for different $\\rho $", fontsize=15)
for i in range(1,11):
    x_holder['x' + str(i)], y_holder['y' + str(i)] = np.loadtxt(f"/workspaces/Computazionale2/GasReticolare/File/A(t)ro={ro*i:.2f}L=80.dat", usecols=(0,1), unpack=True)
    plt.scatter(x_holder['x'+ str(i)], y_holder['y' + str(i)], s=50, label=f'$\\rho ={ro*i:.2f}$', marker=markers[i-1])
plt.plot([], [], '', label='$L=80$', alpha=0)
plt.legend(fontsize=15)
plt.xlabel('Moves', fontsize=15)
plt.ylabel('A(t)', fontsize=15)
plt.grid()
plt.savefig("GasRo.png")