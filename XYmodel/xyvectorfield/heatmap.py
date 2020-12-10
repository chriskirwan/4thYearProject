import matplotlib.pyplot as plt 
import numpy as np

a = np.loadtxt("randomlattice.dat")
b = np.loadtxt("thermalizedlattice.dat")

plt.imshow(a, cmap='hsv')
plt.show()


plt.imshow(b, cmap='hsv')
plt.show()
