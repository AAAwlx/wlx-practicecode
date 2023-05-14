#include<stdio.h>
int Search(int *a,int n,int key,int *mid)
{
    int l=0,r=n-1,f;
    f=0;
    while(l<=r){
        *mid=l+(r-l)/2;
        if(a[*mid]==key){
            f=1;
            break;
        }else{
            *mid=l+(r-l)/2;
            if(a[*mid]>key){
                r=*mid-1;
            }else{
                l=*mid+1;
                
            }
        }
    }
    return f;
}
int main()
{
    int a[100];
    int i,n,key,mid;
    scanf("%d %d",&n,&key);
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    int f=Search(a,n,key,&mid);
    if(f==1){
        printf("已找到，你要找的数坐标为%d",mid);
    }else{
        printf("未找到");
    }
}