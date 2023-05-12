#include<iostream>
#include<vector>
/*void fucn(int value)
{
    std::cout<<"value"<<value<<std::endl;
}*/
void hhh(const std::vector<int>& values,void(*func)(int))
{
    std::cout<<"hello"<<std::endl;
    for(int value:values)
        func(value);
}

int main()
{
    std::vector<int>values={1,2,3,4,5};
    hhh(values,[](int a){std::cout<<"value"<<a<<std::endl;});
}