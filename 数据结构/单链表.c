#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
};
struct node *head;
void weicha(int a)//尾插法创建链表
{
    struct node *p1,*p2;//p1为先前一个指针跟随输入的值移动，p2为后一个指针随着p1的移动而移动
    p1=(struct node *)malloc(sizeof(struct node));
        p1->data=a;
        p1->next=NULL;
        if(head==NULL){
            head=p1;//若为第一个节点就让头指针直接指向节点；
        }else{
            p2->next=p1;//若不是第一个节点，就让上一个节点的next指向新的节点
        }
        p2=p1;//用p2将新一个节点的位置储存下来
}
void toucha(int a)//头插法创建链表
{
    struct node *t1;
    t1=(struct node *)malloc(sizeof(struct node));
    t1->data=a;//读入节点中的数值
    t1->next=head;//该处直接将头指向空与头不指向空两种情况涵盖
    head=t1;
}
void renyicha(int b,int c){//b为要插入的数字，c为要插入的位置
    struct node *q1,*q2;
    q1=(struct node *)malloc(sizeof(struct node));
    q1->data=b;
    q1->next=NULL;
    if(c==1){
        q1->next=head;
        head=q1;
        return;
    }
    q2=head;
    int i;
    for(i=0;i<c-2;i++){
        q2=q2->next;
    }
    q1->next=q2->next;
    q2->next=q1;
}
void shanchu(int d)//d为要删除的位置
{
    int i;
    struct node *h1,*h2;
    h1=head;
    if(d==1){
        head=h1->next;
        free(h1);
    }else{
        for(i=0;i<d-2;i++){
            h1=h1->next;
        }
        h2=h1->next;
        h1->next=h2->next;
        free(h2);
    }
}
void qingkong()
{//清空链表
    struct node *s1 ,*s2;
    s1=head;
    while(s1){
        s2=s1->next;
        free(s1);
        s1=s2;
    }
    head=NULL;
}
void fanzhuan1()//循环反转链表
{
    struct node *current/*代表当前所指节点*/,*prev/*代表当前所指的前一个节点*/,*next/*当前所指的下一个节点*/;
    current=head;
    prev=NULL;
    while(current){
        next=current->next;
        current->next=prev;
        prev=current;//将当前节点的位置交给上一个指针
        current=next;//将下一个节点位置交给当前节点
    }
    head=prev;
}
void fanzhuan2(struct node *p)//递归反转一个链表
{
    if(p->next==NULL){//当最后一个节点的时候使头指针指向该节点
        head=p;
        return;
    }
    fanzhuan2(p->next);//通过递归进入到最后一个节点
    struct node *q=p->next;//将下一个节点的位置交给q暂时储存
    q->next=p;//让下一个节点的next指向当前节点
    p->next=NULL;//该节点后的位置指向空,当此次调用结束后，p被释放，不会对链表中的指向产生影响
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
    int i,n,a,b,c,d;
    scanf("%d",&n);
    head=NULL;
    for(i=0;i<n;i++){
        scanf("%d",&a);
        //weicha(a);
        toucha(a);
        }
    /*scanf("%d %d",&b,&c);
    renyicha(b,c);*/
    Printf();
    /*scanf("%d",&d);
    shanchu(d);
    Printf();
    qingkong();*/
    //fanzhuan1();
    fanzhuan2(head);
    Printf();
    return 0;
}