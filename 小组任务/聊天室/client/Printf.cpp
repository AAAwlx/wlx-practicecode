#include "public.hpp"
#include "clit.hpp"
//存放打印的函数
void Clenit::PrientfT(string s)//将实时消息在顶部显示并在下一次新消息到来时消除
{
    std::cout << "\033[44;37m" << s << "\033[0m" << std::endl;
    std::cout << "\033[F\033[K";
    return ;
}
void Clenit::PrientfR(string s)
{
    int totalWidth = 30;
    std::cout << std::right << std::setw(totalWidth) << s << std::endl;
}
void Clenit::PrientfL(string s)
{
    int totalWidth = 30;
    std::cout << std::left << std::setw(totalWidth) << s << std::endl;
}