#include<stdio.h>
char b[100];
int top=-1;
void push(char a)
{
    b[++top]=a;
}
void pop()
{
    b[top]='\0';
    top--;
}
int Empty()
{
    if(top==-1){
        return 1;
    }else{
        return 0;
    }
}
int main()
{
    char a[100];
    int n,i,len=0,len_max=0;
    scanf("%d",&n);
    for(i=0;i<=n;i++){
        scanf("%c",&a[i]);
        if(a[i]=='('){
            push(i);
        }
        if(a[i]==')'&&Empty()==0){
            pop(i);
            len=i-b[top];
            if(len_max<len){
                len_max=len;
            }
        }
    }
    printf("%d",len_max);
}