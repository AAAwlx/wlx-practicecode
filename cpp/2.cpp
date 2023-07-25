#include <iostream>
#include <utility> // 包含 std::pair 的头文件

int main() {
    std::pair<std::string, int> myPair = std::make_pair("apple", 10);

    // 修改键和值
    myPair.first = "banana"; // 修改键
    myPair.second = 5;       // 修改值

    // 输出修改后的键和值
    std::cout << "Key: " << myPair.first << ", Value: " << myPair.second << std::endl;

    return 0;
}