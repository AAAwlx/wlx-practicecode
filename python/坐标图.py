import matplotlib.pyplot as plt
import numpy as np

# 生成一组x坐标数据
x = np.linspace(0, 2*np.pi, 100)

plt.figure()
# 绘制正弦函数曲线
plt.plot(x, np.sin(x), label='Sine', color='blue')
# 绘制余弦函数曲线)
plt.plot(x, np.cos(x), label='Cosine', linestyle=':', color='g')
plt.xlabel("I'm x")
plt.ylabel("I'm y")
ax = plt.gca() # 将轴线框取出
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.yaxis.set_ticks_position('left')
ax.spines['bottom'].set_position(('data', 0))
ax.spines['left'].set_position(('data', 0))

# 添加图例和标题
plt.legend()
plt.title('Trigonometric Functions')
# 显示网格线
plt.grid()

plt.show()
