#include<iostream>
#include<list>

class jiechu
{
private:
std::string m_name;
public:
    jiechu(const std::string &name)
    :m_name(name){}
    void take()
    {
        std::cout<<m_name<<"给你还钱"<<std::endl;
    }
    ~jiechu()
    {
        printf("1");
    }
};
class jieru
{
public:
    virtual void borrow(jiechu * j)=0;
    virtual void repay()=0;
};
class Zhangsan :public jieru
{
private:
    std::list<jiechu*> zhaizhu;
    int stat=0;//0为没钱
public:
    void borrow(jiechu *j){
        zhaizhu.push_back(j);
    }
    void gaibian()
    {
        stat=1;
    }
    void repay(){
        if(stat==0){
            printf("没钱\n");
        }else{
            for(auto it=zhaizhu.begin();it!=zhaizhu.end();++it){
                (*it)->take();
            }
        }
        
    }
};
int main()
{
    jiechu* l = new jiechu("李四");
    jiechu* w = new jiechu("王麻子");
    Zhangsan* z = new Zhangsan();
    z->borrow(l);
    z->borrow(w);
    z->repay();
    z->gaibian();
    z->repay();
    delete l;
    delete w;
    delete z;
}


