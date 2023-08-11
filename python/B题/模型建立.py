import matplotlib.pyplot as plt
import numpy as np

# 构建坐标点数据
drones = list(range(4))
radii = [0, 10, 10, 10]
angles = [0, 0,119.75, 40.10]
angles_rad = np.radians(angles)
# 创建极坐标图
plt.figure(figsize=(8, 8))
ax = plt.subplot(111, projection='polar')
# 不显示网格线
ax.grid(True)
#设置正方向为顺时针方向
ax.set_theta_direction(1)
#设置极轴指向正东
ax.set_theta_zero_location('E')

# 绘制极坐标散点图
scatter=ax.scatter(angles_rad,radii, c='blue',s=50, alpha=0.75)
for i, (xi, yi) in enumerate(zip(angles_rad, radii)):
    ax.annotate(f'drone{i}', (xi, yi), textcoords="offset points", xytext=(0,3), ha='center')
#连接主动机与被动机
ax.plot([angles_rad[0],angles_rad[-1]],[radii[0],radii[-1]],color='black')
ax.plot([angles_rad[1],angles_rad[-1]],[radii[1],radii[-1]],color='black')
ax.plot([angles_rad[2],angles_rad[-1]],[radii[2],radii[-1]],color='black')
#连接坐标原点与其他各点
ax.plot([angles_rad[0],angles_rad[1]],[radii[0],radii[1]],color='blue',linestyle='dashed')
ax.plot([angles_rad[0],angles_rad[2]],[radii[0],radii[2]],color='blue',linestyle='dashed')
ax.plot([angles_rad[0],angles_rad[-1]],[radii[0],radii[-1]],color='blue',linestyle='dashed')

plt.show()