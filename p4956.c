#include<stdio.h>
int main()
{
    int n,x,k;
    scanf("%d",&n);
    for(int j=1;j<=100;j++){
        for(int i=100;i>0;i--){
            if(j*7+i*21==n/52){
                k=i;
                x=j;
            }
        }
    } 
    printf("%d %d",x,k);
}