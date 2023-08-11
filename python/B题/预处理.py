import math
import matplotlib.pyplot as plt
import numpy as np

def adjust_polar_coordinates(data, target_radius, max_error_percent):
    adjusted_data = []
    for i, entry in enumerate(data):
        if i == 0 or i == 1:  # 不调整0号点和1号点
            adjusted_data.append(entry)
            continue
        
        distance, angle = entry
        error_threshold = target_radius * max_error_percent / 100
        adjusted_distance = target_radius + (distance - target_radius)
        if abs(adjusted_distance - target_radius) <= error_threshold:
            adjusted_data.append((adjusted_distance, angle))
        else:
            adjusted_distance = target_radius + error_threshold if adjusted_distance > target_radius else target_radius - error_threshold
            adjusted_data.append((adjusted_distance, angle))
    return adjusted_data

original_data = [
    (0, 0),
    (100, 0),
    (98, 40.10),
    (112, 80.21),
    (105, 119.75),
    (98, 159.86),
    (112, 199.96),
    (105, 240.07),
    (98, 280.17),
    (112, 320.28)
]

target_radius = 100  # 目标半径
max_error_percent = 5  # 允许的最大误差百分比

adjusted_data = adjust_polar_coordinates(original_data, target_radius, max_error_percent)

# 构造角度数组
angles = [entry[1] for entry in original_data]
adjusted_angles = [entry[1] for entry in adjusted_data]

# 构造距离数组
distances = [entry[0] for entry in original_data]
adjusted_distances = [entry[0] for entry in adjusted_data]

# 将角度数组转换为弧度
angles = np.radians(angles)
adjusted_angles = np.radians(adjusted_angles)

# 绘制极坐标图
plt.figure(figsize=(10, 6))

# 调整前的点（除了0号点和1号点，其余为蓝色）
for i in range(len(original_data)):
    if i == 0 or i == 1:
        plt.polar(angles[i], distances[i], marker='o', color='black')  # 0号点和1号点为黑色
    else:
        plt.polar(angles[i], distances[i], marker='o', linestyle='None', color='blue',label='Original Points')
# 标记位置变动的点为黄色，位置不变的点为绿色
for i in range(2, len(original_data)):
    if abs(adjusted_distances[i] - distances[i]) <= target_radius * max_error_percent / 100:
        plt.polar(adjusted_angles[i], adjusted_distances[i], marker='o', linestyle='None',color='green',label='Unadjusted Points')
    else:
        plt.polar(adjusted_angles[i], adjusted_distances[i], marker='o', linestyle='None',color='yellow',label='Adjusted Points')

plt.title('Polar Coordinates Adjustment')
plt.legend(loc='best')
plt.grid(True)
plt.show()
