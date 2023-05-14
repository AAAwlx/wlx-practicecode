#include<stdio.h>
#include<stdlib.h>
struct node{
    struct node *next;//后半部分指针
    int data;
};
struct node *top;
void push(int a)
{//入栈
    struct node *p;
    p=(struct node*)malloc(sizeof(struct node));
    p->data=a;
    p->next=top;
    top=p;
}
void pop()//出栈
{
    struct node *p;
    if(top==NULL){
        return;
    }
    p=top;
    top=top->next;
    free(p);
}
int Top()
{
    return top->data;
}
void Printf()
{//打印
    struct node *p;
    if(top==NULL){
        printf("NULL");
    }
    p=top;
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}
int main()
{
    top=NULL;
    push(1);
    push(5);
    pop();
    push(4);
    push(11);
    Printf();
}