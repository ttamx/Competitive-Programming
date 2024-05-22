import matplotlib.pyplot as plt
n = int(input())
list_x = []
list_y = []
list_z = []
list_c = []
for _ in range(n):
    x,y,z,c = map(int,input().split())
    list_x.append(x)
    list_y.append(y)
    list_z.append(z)
    list_c.append(c)
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
#display as a box with side length 1
ax.scatter(list_x, list_y, list_z, c=list_c, cmap='viridis')
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')
plt.show()