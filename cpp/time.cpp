#include <iostream>
#include <chrono>

int main() {
    // 获取当前系统时钟的时间点
    auto now = std::chrono::system_clock::now();

    // 将时间点转换为时间戳（以秒为单位）
    std::time_t timestamp = std::chrono::system_clock::to_time_t(now);

    // 打印当前时间戳
    std::cout << "Current timestamp: " << timestamp << std::endl;

    // 获取当前日期和时间的字符串表示
    std::string timeStr = std::ctime(&timestamp);

    // 打印当前日期和时间
    std::cout << "Current time: " << timeStr;

    return 0;
}