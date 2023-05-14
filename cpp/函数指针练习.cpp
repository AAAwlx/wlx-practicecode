#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
/*void fucn(int value)
{
    std::cout<<"value"<<value<<std::endl;
}*/
void hhh(const std::vector<int>& values,/*int(*func)(int)*/const std::function<int(int)>&func)
{
    std::cout<<"hello"<<std::endl;
    for(int value:values){
        int b=func(value);   
    }
        
}

int main()
{
    std::vector<int>values={1,2,3,4,5};
    int a=1;
    
    auto lambda=[=](int value)mutable{
        a++;
        std::cout<<"value"<<value<<a<<std::endl;
        return value;
    };
    hhh(values,lambda);
    std::cout<<a<<std::endl;
    
}