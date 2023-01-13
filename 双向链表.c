#include<stdio.h>
#include<stdlib.h>
struct node{
    struct node *prev;//前半部分指针
    struct node *next;//后半部分指针
    int data;
};
struct node *head;
void toucha(int a)//头插法
{
    struct node *p;
    p=(struct node *)malloc(sizeof(struct node));
    p->prev=NULL;
    p->next=head;
    p->data=a;
    head=p;
}
void weicha(int a)//尾插法
{
    struct node *p1,*p2;
    p1=(struct node*)malloc(sizeof(struct node));
    p1->data=a;
    p1->next=NULL;
    if(head==NULL){
        head=p1;
        p1->prev=NULL;
    }else{
        p2->next=p1;
        p1->prev=p2;
    }
    p2=p1;
}
void renyicha(int b,int c)//任意位置的插入
{
    int i;
    struct node *p1,*p2;
    p1=(struct node*)malloc(sizeof(struct node));
    p1->data=b;
    if(c==1){
        p1->prev=NULL;
        p1->next=NULL;
        head=p1;
    }else{
        p2=head;
        for(i=0;i<c-2;i++){
            p2=p2->next;
        }
        p1->prev=p2;
        p1->next=p2->next;
        p2->next->prev=p1;
        p2->next=p1;
    }
}
void shanchu(int d)
{
    int i;
    struct node *p;
    if(d==1){
        head=p->next;
        p->next->prev=NULL;
        free(p);
    }
    p=head;
    for(i=0;i<d-1;i++){
        p=p->next;
    }
    if(p->next==NULL){
        p->prev->next=NULL;
    }else{
        p->prev->next=p->next;
        p->next->prev=p->prev;
    }
    free(p);
}
void qingkong()
{
    struct node *p1,*p2;
    p1=head;
    while(p1!=NULL){
        p2=p1->next;
        free(p1);
        p1=p2;
    }
}
void Printf()
{//打印链表
    struct node *p;
    if(head==NULL){
        printf("NULL");
    }
    p=head;
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}
int main()
{
    head=NULL;
    int n,i,a,b,c,d;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&a);
        //toucha(a);
        weicha(a);
    }
    scanf("%d %d",&b,&c);
    renyicha(b,c);
    scanf("%d",&d);
    shanchu(d);
    Printf();
}
