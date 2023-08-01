#include <iostream>
#include <unistd.h>
void Prientf(std::string s)
{
    std::cout << "\033[44;37m"<<s<<"\033[0m" << std::endl;
    std::cout << "\033[F\033[K";
    return ;
}
int main() {
    Prientf("xxxxxxxxxxxxx");
    sleep(2);
    Prientf("HHHHHHHHHHHHH");
    sleep(2);
}
