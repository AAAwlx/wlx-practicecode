#include<stdio.h>
#include<string.h>
int main()
{
    char a[100];
    int l,i;
    scanf("%s",a);
    l=strlen(a);
    for(i=l-1;i>=0;i--){
        printf("%c",a[i]);
    }
}