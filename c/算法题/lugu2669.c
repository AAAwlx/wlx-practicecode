#include<stdio.h>
int main()
{
    int k,n=1,i,sum=0;
    int a=n;
    scanf("%d",&k);
    for(i=0;i<k;i++){
        sum+=n;
        a--;
        if(a==0){
            n++;
            a=n;
          //  printf("%d ",n);
        }
    }
    printf("%d",sum);
}
