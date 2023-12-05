# 型别推导
## T模板
### 普通引用或指针
模板型别推导时忽略引用性（指针同理），保留常量性
```cpp
#include<iostream>
template <typename T>
void foo(T &value) {
    std::cout << value << std::endl;
    value = 12;
}

int main() {
    const int x = 42;
    const int& rx = x;
    foo(rx);  // 此时T被实例化为const int，value是const int&
    foo(x);
    std::cout << rx << std::endl;
    return 0;
}
```
### 通用引用
通用引用使用 T &&这样的格式，这是在推导过程中唯一会保留引用性的方式。
```
template<typename T>
void f(T&& param);              //param现在是一个通用引用类型
		
int x=27;                       //如之前一样
const int cx=x;                 //如之前一样
const int & rx=cx;              //如之前一样

f(x);                           //x是左值，所以T是int&，
                                //param类型也是int&

f(cx);                          //cx是左值，所以T是const int&，
                                //param类型也是const int&

f(rx);                          //rx是左值，所以T是const int&，
                                //param类型也是const int&

f(27);                          //27是右值，所以T是int，
                                //param类型就是int&&
```
### 普通的
论传递什么param都会成为它的一份拷贝——一个完整的新对象。事实上param成为一个新对象这一行为会影响T如何从expr中推导出结果。
### 特殊情况
函数和数组在特殊情况下会退化为指针。
```cpp
#include <iostream>

template <typename T>
void PrintType(T value) {
    std::cout << "Type is: " << typeid(value).name() << std::endl;
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    PrintType(&arr);   // 推导的类型是 int*
    PrintType(arr);  // 引用类型保留数组类型，类型是 int [5]
    
    return 0;
}
```
输出结果
>Type is: PA5_i\
Type is: Pi

如果使用引用的方式会被推导为一个数组，否则则是指向一个数组地址的指针。\
但是此时value会被推导为int [5]。此时无法对数组进行修改。

## auto
auto 在大部分情况下与T的推导规则相同，但下列情况会将推导为一个列表，而T不可以。但是Item5解释了使用auto说明符代替指定类型说明符的好处，所以我们应该很乐意把上面声明中的int替换为auto，我们会得到这样的代码：
```
auto x1 = 27;
auto x2(27);
auto x3 = { 27 };
auto x4{ 27 };
```
这些声明都能通过编译，但是他们不像替换之前那样有相同的意义。前面两个语句确实声明了一个类型为int值为27的变量，但是后面两个声明了一个存储一个元素27的 std::initializer_list<int>类型的变量。
