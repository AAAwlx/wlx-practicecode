import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dense
from tensorflow.keras.callbacks import EarlyStopping

# 读取数据
data = pd.read_excel('/home/wlx/pm2.5.xlsx')  # 假设数据保存在名为pm_data.csv的文件中

# 提取特征和标签
features = data[['CO', 'NO2', 'PM10', 'SO2']].values
labels = data['PM2.5'].values

# 归一化特征和标签
scaler = MinMaxScaler()
scaled_features = scaler.fit_transform(features)
scaled_labels = scaler.fit_transform(labels.reshape(-1, 1))

# 划分训练集和测试集
time_steps = 10
train_size = int(0.8 * len(data))
train_features = scaled_features[:train_size - time_steps + 1]
train_labels = scaled_labels[time_steps - 1:train_size]
test_features = scaled_features[train_size - time_steps + 1:]
test_labels = scaled_labels[train_size:]

# 调整数据形状为LSTM所需的三维形状：(样本数, 时间步长, 特征数)
train_features = np.reshape(train_features, (train_features.shape[0], time_steps, train_features.shape[1]))
train_labels = np.reshape(train_labels, (train_labels.shape[0], 1))
test_features = np.reshape(test_features, (test_features.shape[0], time_steps, test_features.shape[1]))
test_labels = np.reshape(test_labels, (test_labels.shape[0], 1))

# 创建LSTM模型
model = Sequential()
model.add(LSTM(units=64, input_shape=(time_steps, train_features.shape[2])))
model.add(Dense(1))

# 编译模型
model.compile(optimizer='adam', loss='mse')

# 定义Early Stopping回调函数
early_stopping = EarlyStopping(monitor='val_loss', patience=5)

# 训练模型
model.fit(train_features, train_labels, epochs=50, batch_size=32, validation_split=0.1, callbacks=[early_stopping])

# 使用训练好的模型进行预测
predicted_labels = model.predict(test_features)

# 将预测值还原为原始范围