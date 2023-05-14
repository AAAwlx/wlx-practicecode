#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<std::string> v = {"hello", "world", "goodbye", "c++"};

    // 按照字符串长度排序
    std::sort(v.begin(),v.end(),[](const std::string &a,const std::string &b){
        return a.length()>b.length();
    });
    for(auto &str:v){
        std::cout<<str<<std::endl;
    }
    return 0;
}