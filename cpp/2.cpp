#include<iostream>
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

int A::count = 0;