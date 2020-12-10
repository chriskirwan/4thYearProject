import matplotlib.pyplot as plt
import numpy as np

mat = np.loadtxt('randomlattice.dat')

size = mat.shape
x = np.arange(0,size[0],1)
y = np.arange(0,size[1],1)

X,Y = np.meshgrid (x,y)
x_shape = X.shape
U = np.zeros(x_shape)
V = np.zeros(x_shape)

for i in range(size[0]):
    for j in range(size[1]):
        U[i,j] = np.sin(mat[i][j])
        V[i,j] = np.cos(mat[i][j])

fig,ax = plt.subplots()
q = ax.quiver(X,Y,U,V,units='xy', scale=2)

ax.set_aspect('equal')

plt.title('Random Lattice for XY Model')
#plt.savefig('thermalized_lattice_vectorfield.png')
plt.show()
