import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# 定义函数以简化代码
def process_data(file_path):
    # 读取数据
    data = pd.read_excel(file_path)
    firstRow = data.iloc[0, :]
    firstColumn = data.iloc[:, 0]
    otherData = data.iloc[1:, 1:]
    constant = 1852

    # 计算行和列的值
    r1 = firstRow * constant
    r2 = firstColumn * constant
    x = r1.iloc[1:].values
    y = r2.iloc[1:].values
    z = otherData * (-1)

    return x, y, z

def plot_contour(x, y, z, contourValues, contourSpacing, title):
    # 绘制等高线图
    plt.figure()
    plt.contour(x, y, z, contourValues)
    plt.contour(x, y, z, levels=np.arange(z.min(), z.max(), contourSpacing))
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title(title)

    # 绘制已知点
    x_known = [4074.4, 4037.36, 4000.32, 3963.28, 3963.28, 3926.24]
    y_known = [7667.28, 7445.04, 7222.8, 7000.56, 6889.44, 6704.24]
    plt.plot(x_known, y_known, 'ro')

    plt.show()

# A 区代码
file_path_A = r'C:\Users\16925\Desktop\附件.xlsx'
x_A, y_A, z_A = process_data(file_path_A)
contourValues_A = [-65.73, -63.9327, -62.2061, -60.6101, -59.7760, -58.6273, 4011]
contourSpacing_A = 1
plot_contour(x_A, y_A, z_A, contourValues_A, contourSpacing_A, '已知数值和其他间距的等高线图')

# B 区代码
file_path_B = r'C:\Users\16925\Desktop\附件.xlsx'
x_B, y_B, z_B = process_data(file_path_B)
contourValues_B = []
contourSpacing_B = 10
plot_contour(x_B, y_B, z_B, contourValues_B, contourSpacing_B, 'B 区域测线设计图')

# C 区代码
file_path_C = r'C:\Users\16925\Desktop\附件.xlsx'
x_C, y_C, z_C = process_data(file_path_C)
contourValues_C = []
contourSpacing_C = 10
plot_contour(x_C, y_C, z_C, contourValues_C, contourSpacing_C, 'C 区域测线设计图')
