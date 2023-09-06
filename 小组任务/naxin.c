#include <stdio.h>
#include <stdlib.h>
/*char* welcome1() {
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
}*/
/*struct structure {
    int foo;
    union {
        int integer;
        char string[11];
        void *pointer;
    } node;
    short bar;
    long long baz;
    int array[7];
};*/
int main()
{
    char *a=(char *)malloc(10);
    printf("");
    printf("%d %ld ",printf("%s %d %ld ",a,scanf("%s",a),sizeof(*a)),sizeof(a));
    free(a);
}
