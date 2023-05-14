#include<iostream>
struct test
{
    int x,y,z;
    char a;
};

int main()
{
    test a={5,8,9,1};
    int *p=(int *)&a;
    int y=*(int *)((short*)&a+5);
    //p=0.0;
    std::cout<<y;
}