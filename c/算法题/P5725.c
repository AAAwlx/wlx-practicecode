#include<stdio.h>
int main()
{
    int i,j,n,b,c,cnt;
    scanf("%d",&n);
    for(i=1;i<=n*n;i++){
        if(i<10){
            printf("0%d",i);
        }else{
            printf("%d",i);
        }
        if(i%4==0){
            printf("\n");
        }
    }
    b=(1+n)*n/2;
    i=n*2;
    while(i>0){//按照剩余的空位判断 
		i-=2;
		for(int j=0;j<i;j++){
			printf(" ");
		}
		for(int j=0;j<(2*n-i)/2;j++){
			cnt++;
			if(cnt<10){
				printf("0");
			}
			printf("%d",cnt);
		}
		printf("\n");
	}
}