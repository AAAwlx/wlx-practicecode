#include <iostream>

int main() {
    std::string message = "This message will be printed at the top of the terminal";

    // 使用 ANSI 转义序列将光标移动到终端最顶部
    std::cout << "\033[44m" << message << "\033[0m" << std::endl;
    std::cout << "Beep sound: \x07" << std::endl;
    // 这里可以继续输出其他内容
    std::cout<<"hhhhh"<<std::endl;
    return 0;
}
