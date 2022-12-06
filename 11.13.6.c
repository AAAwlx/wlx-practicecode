#include<stdio.h>
int is_within(char *a,char b)
{
    int i,t;
    for(i=0;i<10;i++){
        t=0;
        if(a[i]==b){
           t=1;
           break;
        }
    }
    return t;
}
int main()
{
    char a[10];
    scanf("%s",a);
    char b;
    int c;
    scanf("%c",&b);
    printf("%c",b);
    c=is_within(a,b);
    printf("%d",c);
}
