#include<stdio.h>
#include<stdlib.h>

typedef struct  TreeNode//存放每个树节点的信息
{
    int weight;
    int parent;
    int lchild;
    int rchild;
}TreeNode;
typedef struct HFtree
{
    int length;
    TreeNode *data;
}HFtree;

HFtree* init(int *weight,int length)
{
    HFtree *T=(HFtree*)malloc(sizeof(HFtree));
    T->data=(TreeNode*)malloc(sizeof(TreeNode)*(length*2-1));
    T->length=length;
    for(int i=0;i<length;i++){
        T->data[i].weight=weight[i];
        T->data[i].parent=0;
        T->data[i].lchild=-1;
        T->data[i].rchild=-1;
    }
    return T;
}
int* seach(HFtree* T)
{
    int min=1000000,secondmin=1000000;
    int minindex,secondindex;
    for(int i=0; i < T->length; i++){
        if(T->data[i].parent==0){
            if(T->data[i].weight < min){
                min=T->data[i].weight;
                minindex=i;
            }
        } 
    }
    for (int i = 0; i < T->length; i++)
    {
        if(T->data[i].parent==0&&i!=minindex){
            if(T->data[i].weight<secondmin){
                secondmin=T->data[i].weight;
                secondindex=i;
            }
        }
    }
    int *p=(int *)malloc(sizeof(int)*2);
    //printf("%d %d\n",minindex,secondindex);
    p[0]=minindex;
    p[1]=secondindex;
    return p;
}
void Print(HFtree *T,int index)
{
    if(index!=-1){
        printf("%d",T->data[index].weight);
        Print(T,T->data[index].lchild);
        Print(T,T->data[index].rchild);
    }
}
HFtree * creatTree(HFtree* T)
{
    int *p;
    int min,secondmin;
    int n=T->length*2-1;
    for(int i=T->length;i<n;i++){
        p=seach(T);
        min=p[0];
        secondmin=p[1];
        T->data[i].weight=T->data[min].weight+T->data[secondmin].weight;
        T->data[i].lchild=min;
        T->data[i].rchild=secondmin;
        T->data[min].parent=i;
        T->data[secondmin].parent=i;
        T->length++;
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    HFtree *root=init(a,n);
    creatTree(root);
    Print(root,root->length-1);
}