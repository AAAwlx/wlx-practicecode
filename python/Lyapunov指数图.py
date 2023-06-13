
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
# 生成一组随机数据
df = pd.read_excel('/home/wlx/北京污染物.xlsx')
data=df['PM2.5']
time=df['日期']
n=len(data)
# 设置参数
r = 0.01  # 扰动因子
l = np.zeros(n)  # Lyapunov指数数组
l[0] = 0  # 初始值设为0

# 计算Lyapunov指数
for i in range(1, n):
    # 计算当前点和前一个点之间的距离
    dx = abs(data[i] - data[i-1])
    # 计算扰动后的距离
    dy = dx + r
    # 更新Lyapunov指数
    l[i] = l[i-1] + np.log(dy / dx)

# 绘制Lyapunov指数图
plt.plot(l)
plt.xlabel('time')
plt.ylabel('Lyapunov exponent')
plt.show()

