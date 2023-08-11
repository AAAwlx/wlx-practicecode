# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np

# 构建无人机编号、半径和角度数据
drones = list(range(10))
radii = [0, 100, 98, 112, 105, 98, 112, 105, 98, 112]
angles = [0, 0, 40.10, 80.21, 119.75, 159.86, 199.96, 240.07, 280.17, 320.28]

# 转换角度为弧度
angles_rad = np.radians(angles)

# 创建极坐标图
plt.figure(figsize=(8, 8))
ax = plt.subplot(111, projection='polar')

# 绘制极坐标散点图
scatter=ax.scatter(angles_rad, radii, c=drones, cmap='viridis', s=50, alpha=0.75)

# 设置极坐标角度的起点位置
ax.set_theta_offset(np.radians(90))

# 设置极坐标标签
#ax.set_xticks(angles_rad)
ax.set_xticklabels(['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'])

# 添加标题和颜色图例
plt.title("Drone Number Polar Plot")

# 手动指定颜色图例的范围
cbar = plt.colorbar(scatter, ticks=drones)
cbar.set_label("drone number")

# 显示图像
plt.show()