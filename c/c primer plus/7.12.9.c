#include<stdio.h>
int main()
{
    int a,f=1,i,j;
    scanf("%d",&a);
    for(i=2;i<=a;i++){
        for(j=2;j<i;j++){
            if(i%j==0){
                f=0;
                break;
            }
        }
        if(f==1){
            printf("%d ",i);
        }
    }
}