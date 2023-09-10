import math
import pandas as pd#避免分母为零

# 给定参数
alpha = math.radians(1.5)  # 坡度，弧度表示
theta = math.radians(120)  # 多波束开角，弧度表示
o = math.radians(30)
theta2 = math.radians(60)
  # 海域中心点处的海水深度，单位：米
gamma = [0,45,90,135,180,225,270,315]
# 表2中的测线距中心点处的距离
distances = [0,0.3,0.6,0.9,1.2,1.5,1.8,2.1,4]
# 计算覆盖宽度和重叠率
i=0
for g in gamma:
    results1 = []
    print(g)
    for r in distances:
        beat=math.radians(90-g)
        if g<=180:
            deep=120-abs(r*1852*math.tan(alpha)*math.cos(beat))
        else :
            deep = 120+abs(r*1852*math.tan(alpha)*math.cos(beat))
        w = abs(2*deep*math.sin(theta)*math.cos(alpha)/(math.cos(theta)+math.sin(math.radians(3))))
        results1.append([r,w])
    df1 = pd.DataFrame(results1, columns=['测线距中心点处的距离/m','覆盖宽度/m'])
    print(df1)
# 创建DataFrame并保存到xcel文件

#df1.to_excel('result2.xlsx', index=False)
# 打印结果
