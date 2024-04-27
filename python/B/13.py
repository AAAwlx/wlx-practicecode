import sympy as sp
import numpy as np

# 定义常数
n = 0.1
a = np.pi / 120
b = 2 * np.pi / 3

# 初始化数组
array_35 = [0.0] * 35

# 设置第0号元素为 3345.36088471
array_35[0] = 3345.36088471

for i in range(1, 35):
    # 计算方程
    x = array_35[i-1]
    x3 = sp.symbols('x3')
    m = (110 + x * np.tan(a)) * sp.sin(b/2) / (sp.cos(b/2-a)) + (110 + x3 * np.tan(a)) * sp.sin(b/2) / sp.cos(b/2+a)
    k = (110 + x * np.tan(a)) * sp.sin(b) * sp.cos(a) / ((sp.cos(b/2) * sp.cos(a))**2 - (sp.sin(b/2) * sp.sin(a))**2) - (x - x3) * sp.cos(b/2) / sp.cos(b/2+a)
    eqn = k / m - n
    
    # 解方程
    sol = sp.solve(eqn, x3)

    # 获取解的第一个值（假设方程只有一个解）
    x3_value = sol[0].evalf()
    array_35[i] = x3_value
    print(array_35[i])

