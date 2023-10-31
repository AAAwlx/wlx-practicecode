# 型别推导
## 普通引用或指针
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
## 通用引用