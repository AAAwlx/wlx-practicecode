#include<stdio.h>
#define MAX 101
int a[MAX];
int top=-1;
void push(int b)
{
    if(top==MAX-1){
        printf("erorr");
        return;
        }
        a[++top]=b;
}
void pop()
{
    if(top==-1){
        printf("erorr");
        return;
    }
        top--;
}
int Top()
{
    return a[top];
}
void Printf()
{
    int i;
    for(i=0;i<=top;i++){
        printf("%d ",a[i]);
    }
}
int main()
{
    /*push(1);
    push(3);
    pop();
    push(4);
    pop();
    pop();
    push(10);
    push(12);
    Printf();*/
    int i,n,b;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&b);
        push(b);
    }
    pop();
    pop();
    Printf();
}