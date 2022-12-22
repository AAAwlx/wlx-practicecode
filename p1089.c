#include<stdio.h>
int main()
{
    int a,sum1=0,sum2=0,b=1,c;//sum表示交给妈妈的钱的总和，sum2表示津津手中所剩余的钱
    for(int i=1;i<=12;i++){
        scanf("%d",&a);
        sum2+=300;
        sum2-=a;
        if(sum2<0){
            b=0;
            c=i;
            break;
        }
        sum1+=sum2/100;
        sum2%=100;
        printf("%d ",sum2);
    }
    if(b==0){
        printf("%d",c);
    }else{
        printf("%d",sum1*120);
    }
}