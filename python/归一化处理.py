import pandas as pd
from sklearn.preprocessing import MinMaxScaler

# 读取原始数据
data = pd.read_excel('/home/wlx/pm2.5.xlsx')

# 获取需要归一化处理的列
#['平均地表气温(0.1℃)','日最高地表气温(0.1℃)','日最低地表气温(0.1℃)','平均本站气压(0.1hPa)','日最高本站气压(0.1hPa)','日最低本站气压(0.1hPa)','平均风速(0.1m/s)','最大风速(0.1m/s)','最大风速的风向(16方位)','极大风速(0.1m/s)','极大风速的风向(16方位)','20-8时降水量(0.1mm)','8-20时降水量(0.1mm)','20-20时累计降水量(0.1mm)','平均气温(0.1℃)','日最高气温(0.1℃)','日最低气温(0.1℃)','日照时数(0.1小时)','平均相对湿度(1%)','最小相对湿度(仅自记)(1%)','小型蒸发量(0.1mm)','大型蒸发量(0.1mm)']  # 替换为实际的列名
columns_to_normalize = ['PM2.5','PM10','SO2','CO','NO2','O3']
# 创建归一化处理器
scaler = MinMaxScaler()

# 对需要归一化处理的列进行归一化
data[columns_to_normalize] = scaler.fit_transform(data[columns_to_normalize])

# 将结果保存到新表格
data.to_excel('西安气象数据.xlsx', index=False)
