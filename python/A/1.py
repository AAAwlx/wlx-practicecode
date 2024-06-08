import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
 
# 设置中文字体路径（请根据实际情况修改路径）
#font_path = 'C:/Windows/Fonts/simhei.ttf'  # 请替换为实际的字体路径
#font = FontProperties(fname=font_path)
 
# 更新无人机信息
D_max_A = 27  # 最大飞行距离 (km)
Q_max_A = 9  # 最大载重 (kg)
C_fixed_A = 80  # 固定费用 (元/天)
C_per_km_A = 0.8  # 每公里费用 (元/km)
drone_speed = 16.7 / 3.6  # 无人机速度 (km/h), 由 m/s 转为 km/h
 
# 公交站点数据
stations_data = pd.DataFrame({
    'Station_ID': [1, 2, 3, 4, 5, 6, 7, 8, 9],
    'Longitude': [110.125713, 110.08442, 110.029866, 109.962839, 109.956003, 109.920425, 109.839046, 109.823329, 109.767127],
    'Latitude': [32.815024, 32.771676, 32.748994, 32.743622, 32.812194, 32.856136, 32.860495, 32.847468, 32.807855]
})
 
# 需求点数据
demands_data = pd.DataFrame({
    'Demand_ID': range(1, 51),
    'Longitude': [
        110.1053385, 110.1147032, 110.0862574, 110.0435344, 110.0575508,
        110.0386243, 110.0115086, 110.0390602, 110.0246454, 110.0575847,
        109.9456331, 109.9612274, 109.94592, 109.9316682, 109.9245376,
        109.7087533, 109.7748005, 109.7475891, 109.7534532, 109.783015,
        109.7410728, 109.7554844, 109.7147417, 109.8807093, 109.8070677,
        109.9054481, 109.8954509, 109.8979229, 109.8942179, 109.8610985,
        109.8744682, 109.8338804, 109.870924, 109.8292467, 109.8711312,
        109.8813363, 109.978788, 109.8166563, 109.8151216, 109.885638,
        109.9890984, 109.9647812, 109.9303732, 109.9401099, 109.944496,
        109.979708, 109.976757, 109.94999, 109.973673, 109.967765
    ],
    'Latitude': [
        32.77881526, 32.75599834, 32.74905239, 32.74275416, 32.76712584,
        32.70855831, 32.72619993, 32.73965997, 32.72360718, 32.76553658,
        32.7526657, 32.72286471, 32.70899877, 32.73848444, 32.70740885,
        32.7815564, 32.80016336, 32.80903496, 32.85129032, 32.82296929,
        32.82914197, 32.80581363, 32.79995734, 32.89696579, 32.79622985,
        32.89437141, 32.86724756, 32.83444574, 32.83224374, 32.90687042,
        32.89939698, 32.85616627, 32.848223, 32.83825122, 32.88979101,
        32.8642824, 32.75943454, 32.8096699, 32.82822489, 32.84032485,
        32.80854774, 32.80993619, 32.78956582, 32.85264625, 32.802178,
        32.817449, 32.811064, 32.795207, 32.746858, 32.820998
    ],
    'Demand_kg': [3, 4, 2, 0, 8, 7, 4, 9, 10, 6, 7, 12, 3, 5, 6, 5, 3, 13, 12, 3,
                  14, 10, 4, 34, 6, 6, 3, 4, 20, 5, 6, 5, 3, 15, 2, 6, 3, 4, 3, 2,
                  6, 5, 9, 3, 3, 4, 6, 4, 4, 0]
})
 
# 计算两个点之间的距离（Haversine公式）
def haversine(lon1, lat1, lon2, lat2):
    lon1, lat1, lon2, lat2 = map(np.radians, [lon1, lat1, lon2, lat2])
    dlon = lon2 - lon1
    dlat = lat2 - lat1
    a = np.sin(dlat / 2) ** 2 + np.cos(lat1) * np.cos(lat2) * np.sin(dlon / 2) ** 2
    c = 2 * np.arcsin(np.sqrt(a))
    r = 6371  # 地球平均半径（公里）
    return c * r
 
# 将公交站点和需求点的经纬度转换为NumPy数组
stations_lons = stations_data['Longitude'].values
stations_lats = stations_data['Latitude'].values
demands_lons = demands_data['Longitude'].values
demands_lats = demands_data['Latitude'].values
 
# 利用广播机制计算所有公交站点到所有需求点的距离
stations_lons_matrix, demands_lons_matrix = np.meshgrid(stations_lons, demands_lons)
stations_lats_matrix, demands_lats_matrix = np.meshgrid(stations_lats, demands_lats)
distances_matrix = haversine(stations_lons_matrix, stations_lats_matrix, demands_lons_matrix, demands_lats_matrix)
 
# 将距离矩阵转换为字典形式
distances = {(stations_data['Station_ID'][i], demands_data['Demand_ID'][j]): distances_matrix[j, i]
             for i in range(len(stations_data)) for j in range(len(demands_data))}
 
# 发车时间表
bus_schedule = {
    '白河至仓上': [6.67, 8.5, 9, 11, 14, 16.5],
    '仓上至白河': [6, 7.33, 8.83, 11, 14, 15.83]
}
 
# 分配任务并计算总费用，确保每个需求点只被服务一次
def allocate_tasks_and_calculate_costs():
    total_cost = 0
    task_allocation = []
    demand_visited = set()
 
    for demand_id, demand in demands_data.iterrows():
        if demand['Demand_kg'] > Q_max_A:
            continue
 
        best_cost = float('inf')
        best_station = None
 
        # 找到最近的站点
        for station_id, station in stations_data.iterrows():
            station_id = station['Station_ID']
            distance = distances[(station_id, demand['Demand_ID'])]
            if distance <= D_max_A:
                cost = C_fixed_A + 2 * distance * C_per_km_A  # 往返距离
                if cost < best_cost:
                    best_cost = cost
                    best_station = station_id
 
        if best_station is not None and demand['Demand_ID'] not in demand_visited:
            total_cost += best_cost
            task_allocation.append((demand['Demand_ID'], best_station, best_cost))
            demand_visited.add(demand['Demand_ID'])
 
    return total_cost, task_allocation
 
total_cost, task_allocation = allocate_tasks_and_calculate_costs()
 
# 生成具体飞行路径和时刻表
def generate_flight_schedule():
    wait_time = 5 / 60  # 等待时间（小时）
    flight_schedule = []
 
    for direction, times in bus_schedule.items():
        for time in times:
            for task in task_allocation:
                demand_id, station_id, cost = task
                arrival_time = time
                distance = distances[(station_id, demand_id)]
                flight_time = distance / drone_speed  # 按新的飞行速度计算飞行时间
                start_time = arrival_time + wait_time
                end_time = start_time + flight_time
 
                flight_schedule.append({
                    'Direction': direction,
                    'Bus_Arrival_Time': arrival_time,
                    'Demand_ID': demand_id,
                    'Station_ID': station_id,
                    'Flight_Start_Time': start_time,
                    'Flight_End_Time': end_time,
                    'Cost': cost
                })
 
    return flight_schedule
 
flight_schedule = generate_flight_schedule()
 
# 可视化飞行路径
def visualize_flight_paths():
    fig, ax = plt.subplots()
 
    # 绘制公交站点
    ax.scatter(stations_data['Longitude'], stations_data['Latitude'], c='blue', label='公交站点')
 
    # 绘制需求点
    ax.scatter(demands_data['Longitude'], demands_data['Latitude'], c='red', label='需求点')
 
    # 绘制飞行路径
    for task in flight_schedule:  # 显示所有路径
        demand = demands_data.loc[demands_data['Demand_ID'] == task['Demand_ID']].iloc[0]
        station = stations_data.loc[stations_data['Station_ID'] == task['Station_ID']].iloc[0]
        ax.plot([station['Longitude'], demand['Longitude']], [station['Latitude'], demand['Latitude']], c='green')
 
    ax.set_xlabel('Longitude')
    ax.set_ylabel('Latitude')
    ax.set_title('Flight Paths Visualization')
    plt.rcParams['font.sans-serif'] = ['simhei']  # 指定默认字体
    plt.rcParams['axes.unicode_minus'] = False    # 解决保存图像时负号 '-' 显示为方块的问题

    plt.savefig('plot.png')
 
visualize_flight_paths()
 
print(f"最小总费用：{total_cost:.2f} 元")
print("飞行路径和时刻表：")
visited_demands = set()
for flight in flight_schedule:  # 打印所有路径
    if flight['Demand_ID'] not in visited_demands:
        print(f"方向: {flight['Direction']}, 公交车到达时间: {flight['Bus_Arrival_Time']:.2f} 小时")
        print(f"需求点 {flight['Demand_ID']} 从站点 {flight['Station_ID']} 起飞，起飞时间: {flight['Flight_Start_Time']:.2f} 小时，返回时间: {flight['Flight_End_Time']:.2f} 小时，费用: {flight['Cost']:.2f} 元")
        print("-----")
        visited_demands.add(flight['Demand_ID'])