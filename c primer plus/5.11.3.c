#include<stdio.h>
int main()
{
    int a;
    scanf("%d",&a);
    while(a>0){
        printf("%d days are %d weeks, %d days",a,a/7,a%7); 
        scanf("%d",&a);
    }
}