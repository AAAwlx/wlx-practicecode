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
int main()
{
    char a[100];
    int n,i;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%c",&a[i]);
        if(a[i]=='('||a[i]=='['||a[i]=='{'){
            push(a[i]);
        }
        if(a[i]==')'||a[i]==']'||a[i]=='}'){
            pop();
        }
    }
    if(top==0){
        printf("yes");
    }else{
        printf("no");
    }
}