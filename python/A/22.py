# 导入 linprog 函数和所需的 numpy 库
from scipy.optimize import linprog
from fractions import Fraction
import numpy as np
# 定义线性规划问题的系数
# 目标函数系数（需要最小化的函数），如：c = [c1, c2, ..., cn]
c = [0.8, 1.5, 2.5]  # 目标函数是 z = 0.8*x1 + 1.5*x2 + 2.5*x3

# 不等式约束矩阵 A 和向量 b，如：A_ub @ x <= b_ub
A = [
    [Fraction(1, 27), Fraction(1, 16), Fraction(1, 18)],  # 第一个约束：1/27*x1 + 1/16*x2 + 18*x3 <= 108
    [-1, -1, -1],  # 第二个约束：-1*x1 - 1*x2 - 1*x3 <= -164
     [Fraction(10000, 167), Fraction(1000, 15), Fraction(1000, 20)] 

]
b = [108, -164,86400]  # 右侧的常数向量
# 可选：定义变量的上下界
x_bounds = [(0, 164), (0, 164), (0, 164)]  # 例如，所有变量 x1, x2, x3 的取值范围 0 <= xi <= 164

# 将 Fraction 类型转换为浮点数进行计算
#A = [[float(value) for value in row] for row in A]

# 使用 linprog 函数求解线性规划问题
result = linprog(c, A_ub=A, b_ub=b, bounds=x_bounds, method='highs')

# 输出结果
print('Optimal value:', result.fun)          # 最优目标函数值
print('Optimal solution:', result.x)         # 最优解
print('Solver status:', result.message)      # 求解器状态信息
