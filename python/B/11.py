import numpy as np

# 给定参数
a = np.pi / 120  # a
b = 2 * np.pi / 3  # b

# 对每个 d 进行迭代
for d in range(-800, 801, 200):
    # 计算 D
    D = 70 - d * np.tan(a)
    
    # 计算 w
    w = ((70 - d * np.tan(a)) * np.sin(b) * np.cos(a)) / ((np.cos(b / 2) * np.cos(a)) ** 2 - (np.sin(b / 2) * np.sin(a)) ** 2)
    
    # 计算 n
    n = 1 - (200 * np.cos(b / 2) * ((np.cos(b / 2) * np.cos(a)) ** 2 - (np.sin(b / 2) * np.sin(a)) ** 2) / (np.cos(a + b / 2) * (70 - d * np.tan(a)) * np.sin(b) * np.cos(a)))
    
    # 输出结果
    print("For d =", d)  # 测线距中心点处的距离
    print("D =", D)  # 海水深度
    print("w =", w)  # 覆盖宽度
    print("n =", n)  # 与前一条测线的重叠率

