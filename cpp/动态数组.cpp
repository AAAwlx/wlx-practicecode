#include<iostream>
#include<string>
#include<vector>
struct vertex
{
    int x,y,z;
};
std::ostream& operator<<(std::ostream& stream,const vertex& v)
{
    stream<<v.x<<","<<v.y<<","<<v.z;
    return stream;
}
int main()
{
    std::vector<vertex> v;//vector<类型名称> 数组名
    
}
