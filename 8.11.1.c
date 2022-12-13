#include<stdio.h>
int main()
{
    int a,b=0;
    while((a=getchar())!=EOF){
        b++;
    }
    printf("%d",b);
}