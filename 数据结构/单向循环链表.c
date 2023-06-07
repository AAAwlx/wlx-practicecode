#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
};
struct node * Initlist()
{
    struct node *head;
    head=(struct node *)malloc(sizeof(struct node));
    head->data=0;
    head->next=head;
    return head;
}
void Headinsert(struct node *head,int a)
{
    struct node *p=(struct node *)malloc(sizeof(struct node));
    p->data=a;
    p->next=head->next;
    head->next=p;
    head->data++;
}
void Tailinsert(struct node *head,int a)
{
    struct node *p1,*p2;
    p1=(struct node *)malloc(sizeof(struct node));
    p1->data=a;
    p1->next=head;
    if(head->next==head){
        head->next=p1;
    }else{
        p2->next=p1;
    }
    p2=p1;
    head->data++;
}
void Inster(struct node *head,int a,int b)
{
    struct node *q1,*q2;
    q1=(struct node *)malloc(sizeof(struct node));
    q1->data=a;
    q1->next=NULL;
    if(b>head->data){
        printf("插入失败\n");
        return ;
    }
    for(int i=0;i<b;i++){
        q2=q2->next;
    }
    q1->next=q2->next;
    q2->next=q1;
}
void delete(struct node *head,int a)
{
    struct node *p1,*p2;
    p2=head;
    p1=head->next;
    while(p1!=head){
        if(p1->data==a){
            p2->next=p1->next;
            free(p1);
            return ;
        }
        p2=p1;
        p1=p1->next;
    }
    if(p1==head){
        printf("删除失败\n");
    }
}
void clear(struct node *head)
{
    struct node *p1,*p2;
    p1=head->next;
    while(p1!=head){
        p2=p1;
        p1=p1->next;
        free(p2);
    }
    head->next=head;
}
void Printf(struct node *head)
{
    struct node *p;
    p=head->next;
    while(p!=head){
        printf("%d->",p->data);
        p=p->next;
    }
    printf("NULL\n");
}
void player(struct node *head,int n)
{
    struct node *p,*r;
    p=head->next;
    printf("1");
    while (head->data>1)
    {
        for(int i=1;i<n;i++){
            r=p; 
            p=p->next;
            if(p==head){
                i--;
                continue;
            }
        }
        r->next=p->next;
        printf("出局数字为%d\n",p->data);
        free(p);
        head->data--;
        p=r->next;
    }
    printf("胜出数字为%d",head->next->data);
}
int main()
{
    struct node *head=Initlist();
    int a;
    for(int i=5;i>0;i--){
        int a;
        scanf("%d",&a);
        Tailinsert(head,a);
    }
    /*Inster(head,99,1);
    delete(head,4);
    clear(head);
    Printf(head);*/
    player(head,3);
}