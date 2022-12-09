#include<stdio.h>
#include<stdlib.h>
//int a;
int hh(int n)
{
    int a=0;
    a++;
    *p=a;
    if(n==1){
        return 1;
    }else{
        return hh(n-1)+n;
    }
}
int main()
{
    int *p=(int *)malloc(sizeof(int));
    int n;
    scanf("%d",&n);
    hh(n);
    printf("%d",*p);
}