#include<stdio.h>
int main()
{
    char a[50],b[50];
    scanf("%s %s",a,b);
    printf("\"%s%s\"\n",a,b);
    printf("\"%20s%s\"\n",a,b);
    printf("\"%s%-20s\"\n",a,b);
}