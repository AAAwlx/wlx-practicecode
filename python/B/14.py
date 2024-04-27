import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# 读取数据
data = pd.read_excel('/home/ylx/桌面/wlx-dm/python/B/fujian.xlsx', header=None)

# 提取第一行和第一列
firstRow = data.iloc[0, :].values
firstColumn = data.iloc[:, 0].values

# 提取其他数据
otherData = data.iloc[1:, 1:].values

# 定义常数
constant = 1852

# 计算坐标
r1 = firstRow * constant
r2 = firstColumn * constant

# 提取x和y
x = r1[1:]
y = r2[1:]

# 创建网格
X, Y = np.meshgrid(x, y)

# 计算 Z 坐标(地形高度)
z = otherData * (-1)

# 绘制等高线图
fig, axes = plt.subplots(1, 2, figsize=(12, 6))

# 原始等高线图
contour = axes[0].contourf(X, Y, z, levels=30)
plt.colorbar(contour, ax=axes[0])
axes[0].set_title("原始等高线图")

# B 区域测线设计图
contourValues = []
contourSpacing = 10
contour = axes[1].contour(X, Y, z, levels=contourValues)
axes[1].clabel(contour, inline=True, fontsize=8)
contour = axes[1].contour(X, Y, z, levels=np.arange(z.min(), z.max(), contourSpacing), colors='k', linestyles='dashed')
axes[1].set_title("B 区域测线设计图")

plt.show()
