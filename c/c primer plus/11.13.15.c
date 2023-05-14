#include<stdio.h>
int jiancha(char *s)
{
    int i;
    for(i=0;i<10;i++){
        if(s[i]<'0'||s[i]>'9'){
            return 0;
        }
    }
    return 1;
}
int main()
{
    char s[10];
    int a;
    scanf("%s",s);
    a=jiancha(s);
    printf("%d",a);
}