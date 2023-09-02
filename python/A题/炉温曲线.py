import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.optimize import curve_fit

def calculate_q(Ti_next, Ti, Ta, t):
    return (Ti_next - Ti) / (t * (Ta  - Ti))


data = pd.read_excel('/home/wlx/下载/wendu.xlsx')


q_values = []
count=1
# 计算离散的 q 值
for i in range(496,504):
    Ti_next = data.loc[i + 1, '温度(ºC)']
    Ti = data.loc[i, '温度(ºC)']
    Ta = 255+(25-255)*count*0.65/5
    count+=1
    #Ta=235
    t = data.loc[i, '时间(s)']
    q = calculate_q(Ti_next, Ti, Ta, t)
    q_values.append(q)

degree = 5  # 设置多项式的次数
time_steps = data['时间(s)'].iloc[496:504]
coefficients = np.polyfit(time_steps, q_values, degree)
p = np.poly1d(coefficients)
# 打印多项式系数
print("多项式系数：", coefficients)
a,b, c, d,e,f= coefficients
print("拟合曲线方程：y =  %.10f %.10f %.10f %.10f %.10f %.10f" % ( a,b, c, d,e,f))
# 绘制拟合曲线
plt.figure(figsize=(10, 6))
plt.scatter(time_steps, q_values, label="q")
plt.plot(time_steps, p(time_steps), 'r-', label="Furnace temperature curve")
plt.xlabel('Time Step')
plt.ylabel('q Value')
plt.title('Fitted q Value vs. Time Step')
plt.legend()
plt.grid()
plt.show()
