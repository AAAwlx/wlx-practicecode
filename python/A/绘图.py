import matplotlib.pyplot as plt
import numpy as np

# 设置圆的半径和中心
radius = 1
center = (0, 0)

# 创建角度数组
theta = np.linspace(0, 2*np.pi, 100)

# 计算圆的坐标
x = center[0] + radius * np.cos(theta)
y = center[1] + radius * np.sin(theta)

# 创建图形
plt.figure(figsize=(6,6))
plt.plot(x, y)

# 设置轴的比例
plt.gca().set_aspect('equal', adjustable='box')
plt.title('Circle')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.grid(True)

# 保存图形
plt.savefig('/home/ylx/桌面/wlx-dm/circle.png')

# 如果运行环境支持显示图形，取消以下注释
# plt.show()
