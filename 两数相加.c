#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node *next;
};
struct node * weicha(struct node *head,int a)
{
    struct node *p1,*p2;
    p1=(struct node *)malloc(sizeof(struct node));
    p1->data=a;
    p1->next=NULL;
    if(head==NULL){
        head=p1;
    }else{
        p2->next=p1;
    }
    p2=p1;
    return head;   
}
struct node * Sum(struct node *head1,struct node *head2)
{
    int c,f=0;
    struct node *p1,*p2,*head3;
    head3=NULL;
    p1=head1;
    p2=head2;
    while(p1!=NULL&&p2!=NULL){
        c=p1->data+p2->data+f;
        if(c>=10){
            c%=10;
            f=1;
        }else{
            f=0;
        }
        if(p1->next!=NULL||c!=0){
            head3=weicha(head3,c);
        }
        p1=p1->next;
        p2=p2->next;
    }
    return head3;
}
void Printf(struct node *head)
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
    struct node *head1,*head2,*p;
    head1=NULL;
    head2=NULL;
    int a,b,n1,n2,i;
    scanf("%d %d",&n1,&n2);
    if(n1>n2){
        n2=n1;
    }else{
        n1=n2;
    }
    for(i=0;i<n1;i++){
        if(scanf("%d",&a)){
            head1=weicha(head1,a);
        }else{
            head1=weicha(head1,0);
        }
    }
    for(i=0;i<n2;i++){
        if(scanf("%d",&b)){
            head2=weicha(head2,b);
        }else{
            head2=weicha(head2,0);
        }
    }
    p=Sum(head1,head2);
    Printf(p);
}