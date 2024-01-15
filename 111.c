#include <stdio.h>

struct MyStruct
{
    int A;
    char b;
};

int main() {
    struct MyStruct p;
    struct MyStruct* p1 = &p;
    struct MyStruct* p2 = &p;
    printf("%d %d", p1, p2);
    return 0;
}
