#include<iostream>
class HHH
{
public:
    virtual std::string Getname(){return "hhh";}

};

class XXX:public HHH
{
private:
    std::string m_name;
    mutable int a;
public:
    XXX(const std::string &name,int i)
        :m_name(name), a(i){}//初始化链表
    std::string Getname(){return m_name;}
    int li(/*int i*/) const
    {
        a++;
        return a;
    }
};
int main()
{
    HHH *h=new HHH();
    std::cout<< h->Getname()<<std::endl;
    XXX *x=new XXX("123",3);
    std::cout<< x->Getname()<<std::endl;
    HHH *t=x;
    std::cout<< t->Getname()<<std::endl;
    printf("%d",x->li());
}