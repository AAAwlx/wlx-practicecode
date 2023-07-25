/*#include<iostream>
#include<list>
class A
{
private:
    static int count; // 静态成员变量声明
public:
    A(){
        count++;
    }
    void Printf(){
        std::cout << count << std::endl;
    }
    ~A(){}
};

// 静态成员变量初始化

void hhh()
{
    A e;

    e.Printf();
}
int main()
{
    std::list<A> L;
    {
        A a;
        a.Printf(); // 输出 1
        L.emplace_front(a);
        A b;
        b.Printf(); // 输出 2 
        L.emplace_front(b);
    }
    A c=L.back();
    c.Printf();
    A d;
    d.Printf();
    hhh();
}

int A::count = 0;*/
#include <iostream>
#include <list>
#include <string>

int main() {
    std::list<std::pair<std::string, int>> myList;

    // 插入键值对并将值初始化为0
    myList.emplace_back("apple", 0);
    myList.emplace_back("banana", 0);
    myList.emplace_back("orange", 0);

    // 查找键对应的值并更新值
    for (auto& kvp : myList) {
        if (kvp.first == "apple") {
            kvp.second = 10; // 更新值为10
        }
    }

    // 输出所有键值对
    for (const auto& kvp : myList) {
        std::cout << kvp.first << ": " << kvp.second << std::endl;
    }

    return 0;
}