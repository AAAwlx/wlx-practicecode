#include <iostream>
#include <string>

int main() {
    std::string str1 = "Hello, ";
    std::string str2 = "world!";
    std::string str3= str2+str1;

    std::cout << str3 << std::endl;

    return 0;
}
