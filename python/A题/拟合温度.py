import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.optimize import curve_fit
#在曲线上取点
def calculate_points( start, end, step):
    points = []#时间点
    q = []#对应的q值
    x = start
    while x <= end:
        y = 0.0000005727 * x**3 + -0.0000598710 * x**2+0.0021691520 *x+-0.0281486646#拟合后q随着温度变化的方程
        points.append(x)
        q.append(y)
        x += step
    return points,q
# 取点范围和步长
start = 19
end = 1000
step = 0.5
time , q= calculate_points(start, end, step)
#根据拟合好的q曲线计算温度
T = []
T.append(30)#设初始温度为30
for i in range(0,39):
    #初始温度
    Ta = 25
    #欧拉公式
    K1=q[i]*(Ta-T[i])
    c = int(i + time[i] * K1)+1
    K2 = q[c]*(Ta-(T[i] + time[i] * K1))
    new_T = T[i] + (time[i] / 2)*( K1 + K2)
    print(time[i])
    T.append(new_T)
    print(new_T)


data = {
    '时间': time[:39],
    '温度': T[:39],
}
df = pd.DataFrame(data)

# 指定要保存的Excel文件名
csv_filename = './result.csv'

# 将DataFrame写入Excel文件
df.to_csv(csv_filename, index=False)

print(f"数据已写入 {csv_filename}")


