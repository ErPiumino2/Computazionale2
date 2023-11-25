import matplotlib.pyplot as plt
import numpy as np

plt.title('Number of self avoiding random walks trapped over 5000 iterations')
x, y = np.loadtxt("/workspaces/Computazionale2/Lab5/File/SelfAvoidingP.dat", unpack=True)
plt.scatter(y, x, s=2, label='Trapped trajectories', color='r')
#plt.plot(x, y, linestyle=':', color='grey', alpha=0.5)
plt.ylabel('Occurencies')
plt.xlabel('Number of steps')
plt.legend()
plt.savefig('SelfAvoidingP.pdf')