#include<stdio.h>
#include<ctype.h>
int main()
{
    int i,a=0,b=0;
    while((i=getchar())!=EOF){
        if(isupper(i)!=0){
            a++;
        }
        if(islower(i)!=0){
            b++;
        }
    }
    printf("%d %d",a,b);
}