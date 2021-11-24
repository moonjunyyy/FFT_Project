from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

arr = np.loadtxt("../x64/Release/bmpraw.csv", delimiter=',', dtype=np.str_)
arr = np.delete(arr,1291,axis=1);
arr = arr.astype(np.float64)
print(arr)
print(np.shape(arr))

x = np.linspace(0,511,512)
y = np.linspace(0,1290,1291)
x,y = np.meshgrid(x,y)
x = np.transpose(x)
y = np.transpose(y)
print(x)
print(x.shape)
print(y)
print(y.shape)

fig = plt.figure()
ax = fig.gca(projection = '3d')
surf = ax.plot_surface(x,y,arr,antialiased = True)
fig.colorbar(surf,shrink=0.5,aspect=5)
plt.show()