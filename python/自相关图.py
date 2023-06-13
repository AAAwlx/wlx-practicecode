import pandas as pd
import matplotlib.pyplot as plt
import statsmodels.api as sm

# 读取数据
data = pd.read_excel('/home/wlx/pm2.5.xlsx')
data2 = pd.read_excel('/home/wlx/pm2.5.xlsx',sheet_name='Xi an')
# 将日期作为索引
data['日期'] = pd.to_datetime(data['日期'])
data.set_index('日期', inplace=True)
# 绘制自相关图
fig, ax = plt.subplots(figsize=(12, 6))
sm.graphics.tsa.plot_acf(data['PM2.5'], lags=50, ax=ax)
ax.set_title('The autocorrelation plot of PM2.5 concentration in beijing')
plt.show()