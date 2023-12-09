import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure(figsize=(10, 8), dpi=80)
x, y = np.loadtxt("/workspaces/Computazionale2/GasReticolare/File/D(t).dat", usecols=(0,1), unpack=True)
coeff = np.polyfit(x, y, 2, rcond=None, full=False, w=None, cov=False)
xfit = np.linspace(0,1)
plt.plot(xfit, coeff[0]*xfit**2 + coeff[1]*xfit + coeff[2], color='black', label='fit', alpha=0.6)
plt.scatter(x,y, marker='x', s=45, label='Data', color='blue')
plt.plot([], [], '', label='Nsim=5', alpha=0)
plt.plot([], [], '', label='tmax=20.000', alpha=0)
plt.legend()
plt.xlabel('$\\rho$')
plt.ylabel('D(t)')
plt.savefig("GasD.png")