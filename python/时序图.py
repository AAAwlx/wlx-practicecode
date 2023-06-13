import pandas as pd
import matplotlib.pyplot as plt

# 读入数据
data = pd.read_excel('/home/wlx/pm2.5.xlsx')

# 将日期作为索引
data['日期'] = pd.to_datetime(data['日期'])
data.set_index('日期', inplace=True)

# 绘制图表
plt.plot(data.index, data['PM2.5'])

# 添加标签和注释
plt.xlabel('日期')
plt.ylabel('PM2.5')
plt.title('The time series chart of PM2.5 concentration in Beijing')

plt.show()