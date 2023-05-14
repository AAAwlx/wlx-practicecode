#include<stdio.h>
int main()
{
    int a[8]={0},b[34],i,c,j,n,d;
    scanf("%d",&n);
    for(i=0;i<6;i++){
        scanf("%d",&c);
        b[c]=1;//记录获奖号码
    }
    int cnt;
    for(i=0;i<n;i++){
        cnt=0;
        for(j=0;j<7;j++){
            scanf("%d",&d);
            if(b[d]==1){
                cnt++;
            }
        }
        a[cnt]++;
        printf("%d %d|",a[cnt],cnt);
    }
    int sum;
    printf("\n");
    for(i=7;i>0;i--){
        printf("%d ",a[i]);
    }
    
}