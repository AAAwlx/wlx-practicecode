#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
};
struct node *l=NULL;//头指针
struct node *r=NULL;
void Enter(int b)
{
    struct node *p;
    p=(struct node *)malloc(sizeof(struct node *));
    p->data=b;
    p->next=NULL;
    if(r==NULL){
        l=p;
    }else{
        r->next=p;
    }
    r=p;
    //printf("%d",l->data);
}
void Exit()
{
    struct node *p;
    p=l;
    l=l->next;
    if(l==NULL){
        r==NULL;
    }
    free(p);
}
int top()
{
    if(r==NULL){
        printf("队列已为空");
       return 0;
    }
    return r->data;
}
int Empty()
{
    if(r==NULL){
        return 0;
    }else{
        return 1;
    }
}
void Printf()
{
    struct node *p;
    /*if(r==NULL||l==NULL){
        printf("NULL");
    }*/
    p=l;
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
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