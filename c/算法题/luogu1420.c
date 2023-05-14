#include<stdio.h>
int main()
{
    int a[10000],t=1,i,max=1,n;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(i=0;i<n;i++){
        if(a[i]-a[i-1]==1){
            t+=1;
        }else{
            t=1;
        }
        if(max<t){
            max=t;
        }    

    }
    printf("%d",max+1);
}
