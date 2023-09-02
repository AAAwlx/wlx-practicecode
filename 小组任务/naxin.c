#include <stdio.h>
#include <stdlib.h>
char* welcome1() {
    char *a="Welcome to join the Xiyou Linux Group 2023";
    return a;
}
char* welcome2() {
    char b[3]="hhh";
    //请你填入自己的姓名
    return b;
}
int main() {
    char *a=welcome1();
    char *b=welcome2();
    printf("%s:",a);
    printf("%s",b);
    return 0;
}