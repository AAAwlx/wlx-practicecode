#include<stdio.h>
#include<string.h>
void fanxu(char *s1)
{
    int i,l;
    char t;
    l=strlen(s1);
    for(i=0;i<=l;i++){
        t=s1[i];
        s1[i]=s1[l];
        s1[l]=t;
        l--;
    }
}
int main()
{
    char s1[10];
    int i,n;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        getchar();
        scanf("%c",&s1[i]);
    }
    fanxu(s1);
    for(i=0;i<10;i++){
        printf("%c",s1[i]);
    }
}