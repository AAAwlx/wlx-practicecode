import matplotlib.pyplot as plt
import numpy as np

# 构建数据
x = [1, 2, 3, 4, 5]
y = [10, 20, 15, 30, 25]

# 创建图形和坐标轴
fig, ax = plt.subplots()

# 绘制散点图
scatter = ax.scatter(x, y, color='blue', marker='o', s=100, label='Data Points')

# 设置坐标轴标签和标题
ax.set_xlabel('X-axis')
ax.set_ylabel('Y-axis')
ax.set_title('Scatter Plot with Angle Annotation')

# 在每个散点上添加注释文本
for i, (xi, yi) in enumerate(zip(x, y)):
    ax.annotate(f'Point {i}', (xi, yi), textcoords="offset points", xytext=(0,10), ha='center')

# 连接第一个和最后一个散点，绘制虚线
line1 = ax.plot([x[0], x[-1]], [y[0], y[-1]], color='red', linestyle='dashed', linewidth=2, label='Line 1')

# 连接第二个和倒数第二个散点，绘制虚线
line2 = ax.plot([x[1], x[-2]], [y[1], y[-2]], color='green', linestyle='dashed', linewidth=2, label='Line 2')

# 计算夹角角度
angle_rad = np.arctan2(y[-1] - y[0], x[-1] - x[0]) - np.arctan2(y[-2] - y[1], x[-2] - x[1])
angle_deg = np.degrees(angle_rad) % 360  # 将角度限制在0到360之间

# 在图中间位置添加夹角角度标注
mid_x = (x[0] + x[-1]) / 2
mid_y = (y[0] + y[-1]) / 2
ax.annotate(f'{angle_deg:.2f}°', (mid_x, mid_y), textcoords="offset points", xytext=(0,10), ha='center')

# 显示图例
ax.legend()

# 显示图像
plt.show()


