#include<stdio.h>
void fib(int n)
{
    int a=0,b=0,c=1,i;
    printf("1 ");
    for(i=0;i<n-1;i++){
        a=b+c;
        b=c;
        c=a;
        printf("%d ",a);
    }

}
int main()
{
    int n;
    scanf("%d",&n);
    fib(n);
}