import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
import pandas as pd
# 准备数据，并将其转换为LSTM模型所需的形状
def prepare_data(data, seq_length):
    data_X, data_y = [], []
    for i in range(len(data) - seq_length - 1):
        x = data[i:(i+seq_length)]
        y = data[(i+1):(i+seq_length+1)]
        data_X.append(x)
        data_y.append(y)
    return np.array(data_X), np.array(data_y)

data = pd.read_excel('/home/wlx/pm2.5.xlsx')# 加载混沌时间序列数据
data['日期'] = data['日期'].apply(lambda x: int(pd.Timestamp(x).timestamp()))
data = data[['PM2.5','PM10','SO2','CO','NO2']].to_numpy().astype(np.float32)
seq_length = 10
train_size = int(len(data) * 0.7)
train_data = data[:train_size]
test_data = data[train_size:]
X_train, y_train = prepare_data(train_data, seq_length)
X_test, y_test = prepare_data(test_data, seq_length)

# 构建LSTM模型
# 归一化特征和标签
# 归一化特征和标签
model = tf.keras.Sequential([
    tf.keras.layers.LSTM(units=64, input_shape=(None,5)),
    tf.keras.layers.Dense(units=1)
])
model.compile(loss='mean_squared_error', optimizer=tf.keras.optimizers.Adam(), metrics=['accuracy'])
model.fit(X_train, y_train, epochs=50, batch_size=1)

# 对测试集进行预测并还原数据
pred = model.predict(X_test)
pred = np.squeeze(pred)
y_test = np.squeeze(y_test)

# 可视化结果
plt.plot(y_test, label='True Data')
plt.plot(pred, label='LSTM Predict')
plt.xlabel('Time')
plt.ylabel('Value')
plt.legend()
plt.show()
