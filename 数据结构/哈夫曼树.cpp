#include<stdlib.h>
#include <iostream>
#include <unordered_map>
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
typedef struct HuffmanCode {
    char character;
    std::string code;
} HuffmanCode;

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
// Function to generate Huffman Codes for characters
void generateHuffmanCodes(TreeNode *huffmanTree, HuffmanCode *codes, std::string code, int index) {
    if (index < 0) return;
    if (huffmanTree[index].lchild == -1 && huffmanTree[index].rchild == -1) {
        codes[index].code = code;
        codes[index].character = static_cast<char>(index);  // Assuming character codes are used as indices
    }
    generateHuffmanCodes(huffmanTree, codes, code + "0", huffmanTree[index].lchild);
    generateHuffmanCodes(huffmanTree, codes, code + "1", huffmanTree[index].rchild);
}
int main()
{
    int n;
    scanf("%d",&n);
    int a[52];
    FILE *fd = fopen("./text.txt","rw");//以读写的方式打开
    if (fd == NULL) {
        perror("无法打开文件");
        return 1;
    } 
    std::unordered_map<char, int> hashMap;//创建哈希表用来存储出现的次数
    char character;
    // 逐个字符读取文件内容，直到文件结束
    while ((character = getc(fd)) != EOF) {
        hashMap[character]++;
    }
    int i = 0;
    for (auto& pair : hashMap) {//将哈希表中的值放入数组构建树
        a[i++] = pair.second;
        i++;
    }
    HFtree *root=init(a,n);
    creatTree(root);
    Print(root,root->length-1);
}