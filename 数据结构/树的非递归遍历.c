#include<stdio.h>
#include <stdlib.h>
#define MAX 101
typedef struct TreeNode
{
    int data;
    struct TreeNode * left;
    struct TreeNode * right;
    int flag;
}SearchTree;
struct stack 
{     
    SearchTree * data;
    struct stack* next;
};
SearchTree * getnewnode(int data)
{
    SearchTree *T = NULL;
    T = (SearchTree *)malloc(sizeof(SearchTree));
    T->data = data;
    T->right = NULL;
    T->left = NULL;
    T->flag=0;
    return T;
}
SearchTree* insertTree(SearchTree * T, int data)
{
    // 如果为空
    if (T == NULL){
        T=getnewnode(data);
        printf("%d插入树中\n",data);
        return T;
    }
    if (T->data > data){
        T->left = insertTree(T->left, data);
    }else{
        if(T->data < data){
            T->right = insertTree(T->right, data);
        }else{
            printf("%d已在树中，不能再次插入!!!\n",data);
        }
    }
    return T;
}
/*SearchTree * insertTree(SearchTree *root,int data)
{
    if(root==NULL){
        root=getnewnode(data);
    }else{
        root=insertTree(root->left,data);
        root=insertTree(root->right,data);
    }
}*/
struct stack * initstack()
{
    struct stack *head=(struct stack *)malloc(sizeof(struct stack *));
    head->data=NULL;
    head->next=NULL;
    return head;
}
void push(SearchTree *r,struct stack *head)
{
    struct stack *p=(struct stack *)malloc(sizeof(struct stack *));
    p->data=r;
    p->next=head->next;
    head->next=p;
}
int Empty(struct stack *head)
{
    if(head->next==NULL){
        return 0;
    }else{
        return 1;
    }
}
struct stack * pop(struct stack *head)
{
    if(Empty(head)==0){
        return NULL;
    }else{
        struct stack *p=head->next;
        p->data->flag=1;
        head->next=p->next;
        return p;
    }
}
struct stack * gettop(struct stack *head)
{
    if(Empty(head)==0){
        return NULL;
    }else{
        return head->next;
    }
}
void Preorder(SearchTree *r)
{
    SearchTree *node=r;
    struct stack *head=initstack();
    while(node||Empty(head)==1){
        if(node){
            printf("%d ",node->data);
            push(node,head);
            node=node->left;
        }else{
            node=pop(head)->data;
            //printf("%d ",node->data);//在此位置访问节点值为中序
            node=node->right;
        }
    }
}
void Postorder(SearchTree *r)
{
    SearchTree *node=r;
    struct stack *head=initstack();
    while(node||Empty(head)==1){
        if(node){
            push(node,head);
            node=node->left;
        }else{
            SearchTree *top=gettop(head)->data;
            if(top->right&&top->right->flag==0){
                top=top->right;
                push(top,head);
                node=top->left;
            }else{
                top=pop(head)->data;
                printf("%d ",top->data);//在此位置访问节点值为中序
                top->flag=1;
            }
        }
    }
}
int main()
{
    SearchTree *root=NULL;
    int data[7] = {45,24,53,28,12,50,90};
    int i;
    for(i=0;i<7;i++){
        root = insertTree(root,data[i]);
    }
    //Preorder(root);
    Postorder(root);
    printf("\n");
    Preorder(root);
}
