#include<stdio.h>
int main()
{
    int a[100],b[100]={0},i,j,t=0,n;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(i=0;i<n;i++){
        j=a[i];
        b[j]+=1;
        if(j>t){
            t=j;
        }
    }
    for(j=0;j<=t;j++){
        if(b[j]==1){
            printf("%d ",j);
        }
    }
}
