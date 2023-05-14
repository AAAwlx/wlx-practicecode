import matplotlib.pyplot as plt
import numpy as np

# 生成一些随机数据
x = np.random.normal(size=10)
y = np.random.normal(size=10)

# 创建一个散点图
fig, ax = plt.subplots()
ax.scatter(x, y)

# 标注第一个数据点的值
ax.annotate(f'({x[0]:.2f}, {y[0]:.2f})', xy=(x[0], y[0]),
            xytext=(x[0]+0.5, y[0]+0.5), fontsize=12,
            arrowprops=dict(facecolor='blue', shrink=0.05),
            ha='center', va='bottom')

# 添加标题和轴标签
ax.set_title('Scatter Plot with Annotation')
ax.set_xlabel('X-axis')
ax.set_ylabel('Y-axis')
plt.show()