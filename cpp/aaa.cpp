#include <iostream>
#include <deque>
template<typename Container, typename Index>    //C++14版本，
decltype(auto) authAndAccess(Container&& c, Index i)       //不那么正确
{
    //return c[i];
    return std::forward<Container>(c)[i];  // 从c[i]中推导返回类型
}
std::deque<int> makeStringDeque()
{
    std::deque<int> d;
    d.emplace_front(1);
    return d;
}
int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    std::cout<<typeid(authAndAccess(makeStringDeque(), 0) ).name()<<std::endl;  

    return 0;
}