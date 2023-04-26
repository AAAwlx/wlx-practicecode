#include<iostream>
#include<string.h>
class Example
{
private:
    int buffer_size;
    char *buffer;
public:
    Example(char *string){
        buffer_size=strlen(string);
        buffer=new char[buffer_size+1];
        memcpy(buffer,string,buffer_size+1);
    }
    Example(const Example &other)
    :buffer_size(other.buffer_size)
    {
        std::cout<<"hhh"<<std::endl;
        buffer=new char[buffer_size+1];
        memcpy(buffer,other.buffer,buffer_size+1);
    }
    char& operator[](unsigned int index)
    {
        return buffer[index];
    }
    ~Example(){
        delete[] buffer;
    }
    friend std::ostream& operator<<(std::ostream &stream,const Example&example);
};
std::ostream& operator<<(std::ostream &stream,const Example&string)
{
    stream<< string.buffer;
    return stream;
}
void Printf(Example &string)
{
    std::cout<< string <<std::endl;
}
int main()
{
    Example string="abcef";
    Example string2=string;
    string2[2]=' ';
    Printf(string);
    Printf(string2);
}