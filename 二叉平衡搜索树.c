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
AVLTree* Search(AVLTree * T, int data)
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
AVLTree* rrRotation(AVLTree *T)//得到根节点以及指向根节点的指针
{
    AVLTree *temp=T->right;//得到中间节点
    T->right=temp->left;//假如中间节点有左孩子，就让中间节点的左孩子成为根节点的右孩子
    temp->left=T;//让根节点作为中间节点的左节点
    temp->hight=MAX(GET_HEIGHT(temp->left),GET_HEIGHT(temp->right))+1;//分别得到调整之后中间节与根的树高
    T->hight=MAX(GET_HEIGHT(T->left),GET_HEIGHT(T->right))+1;
    return temp;//调整后中间节点变为根节点
}
AVLTree* llRotation(AVLTree *T)
{
    AVLTree *temp=T->left;
    T->left=temp->right;
    temp->right=T;
    temp->hight=MAX(GET_HEIGHT(temp->left),GET_HEIGHT(temp->right))+1;
    T->hight=MAX(GET_HEIGHT(T->left),GET_HEIGHT(T->right))+1;
    return temp;
}
AVLTree* fixed(AVLTree *T,int data)
{
    if(GET_HEIGHT(T->left)-GET_HEIGHT(T->right)==2){
        if(T->left->data > data){
            T=llRotation(T);
        }else{
            T->left=rrRotation(T->left);
            T=llRotation(T);
            }
    }else if(GET_HEIGHT(T->right)-GET_HEIGHT(T->left)==2){
            if(T->right->data < data){
              T=rrRotation(T);
            }else{
                T->right=llRotation(T->right);
                T=rrRotation(T);
            }
    }
    return T;
}
AVLTree* insertTree(AVLTree *T, int data)
{
    // 如果为空
    if (T == NULL){
        T=getnewnode(data);
        printf("%d插入树中\n",data);
        T->hight=MAX(GET_HEIGHT(T->left),GET_HEIGHT(T->right))+1;
        return T;
    }
    if (T->data > data){
        T->left = insertTree(T->left, data);
        T=fixed(T,data);
    }else{
        if(T->data < data){
            T->right = insertTree(T->right, data);
            T=fixed(T,data);
        }else{
            printf("%d已在树中，不能再次插入!!!\n",data);
        }
    }
    T->hight=MAX(GET_HEIGHT(T->left),GET_HEIGHT(T->right))+1;
    return T;
}
//删除节点
AVLTree* findMax2(AVLTree* T)
{
    AVLTree* p=T;
    while(p->right!=NULL){
        p=p->right;
    }
    return p;
}
AVLTree*  Delete(AVLTree * T,int data)
{
    if(T==NULL) return T;
    else if(data<T->data) T->left = Delete(T->left,data);
	else if(data>T->data) T->right = Delete(T->right,data);
    else{
        if(T->left==NULL&&T->right==NULL){
            free(T);
            T=NULL;
        }
        else if(T->right==NULL){
                AVLTree *temp=T;
                T=T->left;
                free(temp);
        }
        else if(T->left==NULL){
                AVLTree *temp=T;
                T=T->right;
                free(temp);
        }
        else{
            AVLTree *temp=findMax2(T->left);
            T->data=temp->data;
            T->left=Delete(T->left,temp->data);
        }
    }
    if(T){
        T=fixed(T,data);
        T->hight=MAX(GET_HEIGHT(T->left),GET_HEIGHT(T->right))+1;
    }
    return T;
}
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
    int a[9]={1,2,3,4,5,6,7,8,9};
    AVLTree *T=NULL;
    for(i=0;i<9;i++){
        T=insertTree(T,a[i]);
    }
    Preorder(T);
    Delete(T,5);
    printf("\n");
    Preorder(T);
}