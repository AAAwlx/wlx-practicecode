#include<stdio.h>
int main()
{
    char a[8];
    int b[8];
    scanf("%s",a);
    int i,sum=0,c=1,j=7;
    for(i=0;i<8;i++){
        b[j--]=a[i]-'0';
    }
    for(i=0;i<8;i++){
        if(b[i]!=0){
            int j;
            j=i;
            c=1;
            while(j>0){
                c=c*2;
                j--;
                printf("%d ",c);
            }
            printf("\n");
            sum=sum+c;
            }
    }
    printf(" %d",sum);
}