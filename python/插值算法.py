# mathmodel24_v1.py
# Demo24 of mathematical modLSing algorithm
# Demo of interpolate with Scipy.interpolate
# Copyright 2021 YouCans, XUPT
# Crated：2021-08-01

# 2. 一维插值方法(内插)比较
import numpy as np
import matplotlib.pyplot as plt  # 导入 Matplotlib 工具包
from scipy.interpolate import interp1d  # 导入 scipy 中的一维插值工具 interp1d

# 生成已知数据点集 (x,y)，需插值的数据点集 xnew
np.random.seed(5)
x = np.linspace(0, 5, 10)  # 生成已知数据点集的 x
y = np.cos(x/10)*2 + 0.5*np.random.rand(10)  # 生成已知数据点集的 y
xnew = np.linspace(0, 5, 100)  # 指定需插值的数据点集 xnew

# 使用不同插值方法，由给定数据点集 (x,y) 求插值函数 fx
f1 = interp1d(x, y, kind="linear")  # 线性插值
f2 = interp1d(x, y, kind="zero")  # 零阶样条插值
f3 = interp1d(x, y, kind="slinear")  # 一次样条插值
f4 = interp1d(x, y, kind="quadratic")  # 二次样条插值
f5 = interp1d(x, y, kind="cubic")  # 三次样条插值
f6 = interp1d(x, y, kind="nearest")  # 临近点插值，向下舍入
# f7 = interp1d(x, y, kind="nearest-up")  # 临近点插值，向上舍入
f8 = interp1d(x, y, kind="previous")  # 前点插值
f9 = interp1d(x, y, kind="next")  # 后点插值

# 绘图
plt.figure(figsize=(8,6))
plt.suptitle("Data interpolate")  # 全局标题
plt.subplot(221)
plt.plot(x, y, "o",  label="data")  # 已知数据点
plt.plot(xnew, f2(xnew), label="0-order spline")  # 零阶样条插值
plt.plot(xnew, f3(xnew), label="1-order spline")  # 一阶样条插值
plt.legend(loc="lower left")
plt.subplot(222)
plt.plot(x, y, "o",  label="data")  # 已知数据点
plt.plot(xnew, f4(xnew), label="2-order spline")  # 二阶样条插值
plt.plot(xnew, f5(xnew), label="3-order spline")  # 三阶样条插值
plt.legend(loc="lower left")
plt.subplot(223)
plt.plot(x, y, "o",  label="data")  # 已知数据点
plt.plot(xnew, f1(xnew), label="linear")  # 线性插值
plt.plot(xnew, f6(xnew), label="nearest")  # 临近点插值，向下舍入
# plt.plot(xnew, f7(xnew), label="nearest-up")  # 临近点插值，向上舍入
plt.legend(loc="lower left")
plt.subplot(224)
plt.plot(x, y, "o",  label="data")  # 已知数据点
plt.plot(xnew, f8(xnew), label="previous")  # 前点插值
plt.plot(xnew, f9(xnew), label="next")  # 后点插值
plt.legend(loc="lower left")
plt.show()
