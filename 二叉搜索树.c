#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct TreeNode
{
    int data;
    struct TreeNode * left;
    struct TreeNode * right;
}SearchTree;

typedef struct{     
    int front, rear;
    SearchTree * data[MAX];
} Queue;//队列的结构体
//队列相关的操作
void initQueue (Queue *q);//初始化队列
int EmptyQueue(Queue *q);//判断是否为空
SearchTree * DeQueue(Queue *q);//出队
void InQueue(SearchTree *t,Queue *q);//入队

SearchTree * getnewnode(int data)
{
    SearchTree *T = NULL;
    T = (SearchTree *)malloc(sizeof(SearchTree));
    T->data = data;
    T->right = NULL;
    T->left = NULL;
    return T;
}
SearchTree * Search(SearchTree * T, int data)
{
    if(T==NULL){
        return T;
    }else{
        if(T->data==data){
            return T;
        }else{
            if(data<=T->data){
                return Search(T->left, data);
            }else{
                return Search(T->right, data);
            }
        }
    }
}
// 插入
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
// 寻找树的最小节点
SearchTree* FindMin(SearchTree * T)
{
    if (T == NULL)
    {
        printf("该树为空");
    }
    if (T->left != NULL)
    {
        return FindMin(T->left);
    }
    return T;
}
// 寻找树的最大节点
SearchTree* findMax(SearchTree * T)
{
    if (T == NULL)
    {
        printf("该树为空");
    }
    if (T->right != NULL)
    {
        return findMax(T->right);
    }
    return T;
}
SearchTree* findMax2(SearchTree * T)
{
    SearchTree* p=T;
    while(p->right!=NULL){
        p=p->right;
    }
    return p;
}
int max(int a,int b)
{
    if(a>b){
        return a;
    }else{
        return b;
    }
}
//最大深度
int deepfind(SearchTree * T)
{
    if(T==NULL){
        return -1;
    }else{
        return max(deepfind(T->left),deepfind(T->right))+1;
    }
}
//广度优先
void Leveolder(SearchTree * T,Queue *q)
{
    SearchTree *t=T;
    if(t==NULL){
        printf("该树为空\n");
        return;
    }
    InQueue(t,q);
    while(EmptyQueue(q)==0){
        t=DeQueue(q);
        printf("%d ",t->data);
        if(t->left!=NULL){
            InQueue(t->left,q);
        }
        if(t->right!=NULL){
            InQueue(t->right,q);
        }
    }
}
//深度优先
void Preorder(SearchTree * T)
{
    if(T==NULL){
        return;
    }
    Preorder(T->left);
    printf("%d ",T->data);
    Preorder(T->right);
}
//判断是否为二叉搜索树
int panduan(SearchTree * T)
{
    int f;
    if(T==NULL){
        return 1;
    }else{
        int a=panduan(T->left);
        if(T->data<f||a==0){
            return 0;
        }
        f=T->data;
        int b=panduan(T->right);
        return b;
    }    
}
SearchTree*  Delste(SearchTree * T)
{
    if(T==NULL){
        return T;
    }else{
        if(T->left==NULL&&T->right==NULL){
            free(T);
            T=NULL;
        }else{
            if(T->right==NULL){
                SearchTree *temp=T;
                T=T->left;
                free(temp);
            }else{
                if(T->left==NULL){
                    SearchTree *temp=T;
                    T=T->right;
                    free(temp);
                }else{
                    SearchTree *temp=findMax2(T->left);
                    T->data=temp->data;
                    T->left=Delste(T->left);
                }
                
            }
        }
        return T;
    }
}
int main (void)
{
    int data[7] = {45,24,53,28,12,50,90};
    int i;
    SearchTree *root = NULL; //二叉查找树根节点
    for(i=0;i<7;i++)    //创建二叉查找树
    {
        root = insertTree(root,data[i]);
    }
    findMax(root);
    SearchTree *j=Search(root,53);
    if(j!=NULL){
        printf("已找到");
    }else{
        printf("未找到");
    }
    SearchTree *p=findMax(root);
    printf("最大值为%d\n",p->data);
    int b=deepfind(root);
    printf("最大深度为%d\n",b);
    Queue q;
	initQueue(&q);
    Leveolder(root,&q);
    printf("\n");
    Preorder(root);
    printf("\n");
    Delste(Search(root,53));
    Preorder(root);
    int d=panduan(root);
    if(d==1){
        printf("是排序二叉树");
    }else{
        printf("不是排序二叉树");
    }
}
void initQueue (Queue *q)   //初始化队列
{
 q->rear=0;
 q->front=0;
}
int EmptyQueue(Queue *q)   //判断队列是否为空 
{
    if(q->rear==q->front)
	    return 1;
    else
	    return 0;
}
SearchTree * DeQueue(Queue *q)    //队尾删除一个元素 
{
  return q->data[(q->front)++];
}
 
void InQueue(SearchTree *t,Queue *q)   //队头一个元素 
{
    if(q->rear==MAX){
	    printf("队列已满!"); 
    }else{
        q->data[(q->rear)++]=t;
    }
}