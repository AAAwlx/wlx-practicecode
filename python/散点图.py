import matplotlib.pyplot as plt

# x和y是两个包含数据的列表
x = [1, 2, 3, 4, 5]
y = [2, 4, 6, 8, 10]

# 创建散点图
plt.scatter(x, y)

# 添加标题和标签
plt.title('Scatter Plot Example')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')

# 显示图形
plt.show()
