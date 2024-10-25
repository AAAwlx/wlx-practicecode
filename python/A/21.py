# 导入 linprog 函数和所需的 numpy 库
from scipy.optimize import linprog
import numpy as np

# 定义线性规划问题的系数
# 目标函数系数（需要最小化的函数），如：c = [c1, c2, ..., cn]
c = [80, 150, 200]  # 例如，目标函数是 z = 80*x1 + 150*x2 + 200*x3

# 不等式约束矩阵 A 和向量 b，如：A_ub @ x <= b_ub
A = [
    [-9, -30, -50],  # 例如，第一个约束：9*x1 + 30*x2 + 50*x3 >=321
    [1, 1, 1],  # 第二个约束：1*x1 + 1*x2 + 1*x3 <= 108
    [-27, -9, -18]   # 第三个约束：27*x1 + 9*x2 + 18*x3 >= 164
]
b = [-10, 12, -11]  # 右侧的常数向量

# 可选：定义变量的上下界
# 如果没有定义，默认为 (0, None) 即变量 x >= 0
x_bounds = [(0, None), (0, None), (0, None)]  # 例如，所有变量 x1, x2, x3 >= 0

# 使用 linprog 函数求解线性规划问题
result = linprog(c, A_ub=A, b_ub=b, bounds=x_bounds, method='highs')

# 输出结果
print('Optimal value:', result.fun)          # 最优目标函数值
print('Optimal solution:', result.x)         # 最优解
print('Solver status:', result.message)      # 求解器状态信息
