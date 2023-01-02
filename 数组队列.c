#include<stdio.h>
#define MAX 101
int a[MAX];
int r=-1,l=-1;
void Enter(int b)
{
    if(r==-1){
        l+=1;
    }
    a[(r+1)%MAX]=b;
    r++;
}
void Exit()
{
    l++;
    printf("%d",l);
}
int top()
{
    return a[r];
}
int Empty()
{
    if((r==-1&&l==-1)||l>r){
        return 0;
    }else{
        return 1;
    }
}
void Printf()
{
    int i;
    for(i=l;i<=r;i++){
        printf("%d",a[i]);
    }
}
int main()
{
    Enter(1);
    Enter(2);
    Enter(3);
    Exit();
    Printf();
}