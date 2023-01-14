#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b)   (a > b ? a : b)
#define GET_HEIGHT(T)   (T ? T->hight:0)
typedef struct TreeNode
{
    int data,hight;
    struct TreeNode * left;
    struct TreeNode * right;
}AVLTree;
AVLTree * getnewnode(int data)
{
    AVLTree *T = NULL;
    T = (AVLTree *)malloc(sizeof(AVLTree *));
    T->data = data;
    T->hight=0;
    T->right = NULL;
    T->left = NULL;
    return T;
}
void rrRotation(AVLTree *T,AVLTree **root)//得到根节点以及指向根节点的指针
{
    AVLTree *temp=T->right;//得到中间节点
    T->right=temp->left;//假如中间节点有左孩子，就让中间节点的左孩子成为根节点的右孩子
    temp->left=T;//让根节点作为中间节点的左节点
    temp->hight=MAX(GET_HEIGHT(temp->left),GET_HEIGHT(temp->right))+1;//分别得到调整之后中间节与根的树高
    T->hight=MAX(GET_HEIGHT(T->left),GET_HEIGHT(T->right))+1;
    *root=temp;//调整后中间节点变为根节点
}
void llRotation(AVLTree *T,AVLTree **root)
{
    AVLTree *temp=T->left;
    T->left=temp->right;
    temp->right=T;
    temp->hight=MAX(GET_HEIGHT(temp->left),GET_HEIGHT(temp->right))+1;
    T->hight=MAX(GET_HEIGHT(T->left),GET_HEIGHT(T->right))+1;
    *root=temp;
}
// 插入节点
AVLTree* insertTree(AVLTree** T, int data)
{
    // 如果为空
    if (*T == NULL){
        *T=getnewnode(data);
        printf("%d插入树中\n",data);
        (*T)->hight=MAX(GET_HEIGHT((*T)->left),GET_HEIGHT((*T)->right))+1;
        return *T;
    }
    if ((*T)->data > data){
        (*T)->left = insertTree(&(*T)->left, data);
        int lh=GET_HEIGHT((*T)->left);
        int rh=GET_HEIGHT((*T)->right);
        if(lh-rh==2){
            if((*T)->left->data > data){
                llRotation(*T,T);//LL
            }else{
                rrRotation((*T)->left,&(*T)->left);
                llRotation(*T,T);//lr
            }
        }
    }else{
        if((*T)->data < data){
            (*T)->right = insertTree(&(*T)->right, data);
            int lh=GET_HEIGHT((*T)->left);
            int rh=GET_HEIGHT((*T)->right);
            if(rh-lh==2){
            if((*T)->right->data < data){
                rrRotation(*T,T);
            }else{
                llRotation((*T)->right,&(*T)->right);
                rrRotation(*T,T);
            }
        }
        }else{
            printf("%d已在树中，不能再次插入!!!\n",data);
        }
    }
    (*T)->hight=MAX(GET_HEIGHT((*T)->left),GET_HEIGHT((*T)->right))+1;
    return (*T);
}
//删除节点
void Preorder(AVLTree * T)
{
    if(T==NULL){
        return;
    }
    printf("%d ",T->data);
    Preorder(T->left);
    Preorder(T->right);
}
int main()
{
    int i;
    int a[5]={1,8,6,7,10};
    AVLTree *T=NULL;
    for(i=0;i<5;i++){
        insertTree(&T,a[i]);
    }
    Preorder(T);
}