import math
import pandas as pd

# 给定参数
alpha = math.radians(1.5)  # 坡度，弧度表示
theta = math.radians(120)  # 多波束开角，弧度表示
o = math.radians(30)
theta2 = math.radians(60)
D0 = 70  # 海域中心点处的海水深度，单位：米

# 表1中的测线距中心点处的距离
distances1 = [-800, -600, -400, -200]
distances2 = [200, 400, 600, 800]
# 计算覆盖宽度和重叠率
results1 = []
for r in distances1:
    deep=2*(70+r*math.tan(alpha))#距离中心的深度
    a = deep * math.sin(theta)*math.cos(alpha)
    b = math.cos(theta)+math.cos(o)
    w = a/b#覆盖宽度
    overlap = 1-r*b/2*deep*math.sin(theta)*math.cos(alpha)*(math.cos(alpha)+1/math.tan(theta2)) # 重叠率
    results1.append([r, deep, w ,overlap])
results2 = []
for r in distances2:
    deep=2*(70-r*math.tan(alpha))#距离中心的深度
    a = deep * math.sin(theta)*math.cos(alpha)
    b = math.cos(theta)+math.cos(o)
    w = a/b#覆盖宽度
    overlap = 1-r*b/2*deep*math.sin(theta)*math.cos(alpha)*(math.cos(alpha)+1/math.tan(theta2)) # 重叠率
    results2.append([r, deep, w ,overlap])
# 创建DataFrame并保存到xcel文件
df1 = pd.DataFrame(results1, columns=['测线距中心点处的距离/m', '覆盖宽度/m', '与前一条测线的重叠率/%'])
df2 = pd.DataFrame(results1, columns=['测线距中心点处的距离/m', '覆盖宽度/m', '与前一条测线的重叠率/%'])
df1.to_excel('result1.xlsx', index=False)

# 打印结果
print(df1)
print(df2)
