#include<stdio.h>
int main()
{
    int a,o=0,j=0,sum1=0,sum2=0;
    scanf("%d",&a);
    while(a>0){
        if(a%2==0){
            sum1=sum1+a;
            o++;
        }else{
            sum2=a+sum2;
            j++;
        }
        scanf("%d",&a);
    }
    printf("%d %d %d %d",o,sum1/o,j,sum2/j);
}