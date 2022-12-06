#include<stdio.h>
void yuan(int a[3][5])
{
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<5;j++){
            printf("%d",a[i][j]);
        }
        printf("\n");
    }
}
void bei(int a[3][5])
{
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<5;j++){
            printf("%d",a[i][j]*2);
        }
        printf("\n");
    }
}
int main()
{
    int a[3][5],i,j;
    for(i=0;i<3;i++){
        for(j=0;j<5;j++){
            a[i][j]=1;
        }
    }
    yuan(a);
    bei(a);
}
