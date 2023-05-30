#include<iostream>
class Base
{
    public:
    Base(){std::cout<<"111"<<std::endl;}
    virtual ~Base(){std::cout<<"222"<<std::endl;}
};
class Deeived: public Base
{
    public:
    Deeived(){std::cout<<"333"<<std::endl;}
    ~Deeived(){std::cout<<"444"<<std::endl;}
};
int main()
{
    Base *a=new Base();
    delete a;
    printf("_____\n");
    Deeived *b=new Deeived();
    delete b;
    printf("_____\n");
    Base *p=new Deeived();
    delete p;
}
/*不使用虚析构函数的危害:
派生类中的析构函数不会被调用，当成员函数中申请内存后，内存没有被释放，会导致内存泄漏
*/