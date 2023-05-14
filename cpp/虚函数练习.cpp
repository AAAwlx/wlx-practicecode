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
public:
    XXX(const std::string &name)
        :m_name(name){}
    std::string Getname(){return m_name;}
};
int main()
{
    HHH *h=new HHH();
    std::cout<< h->Getname()<<std::endl;
    XXX *x=new XXX("123");
    std::cout<< x->Getname()<<std::endl;
    HHH *t=x;
    std::cout<< t->Getname()<<std::endl;
}