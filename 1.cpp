#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>

std::unordered_map<char, int> hashMap;

typedef struct TreeNode {
    int weight;
    int parent;
    int lchild;
    int rchild;
} TreeNode;

typedef struct HFtree {
    int length;
    TreeNode *data;
} HFtree;

// Structure to store Huffman Codes
typedef struct HuffmanCode {
    char character;
    std::string code;
} HuffmanCode;

HFtree *init(int *weight, int length) {
    HFtree *T = (HFtree *)malloc(sizeof(HFtree));
    T->data = (TreeNode *)malloc(sizeof(TreeNode) * (length * 2 - 1));
    T->length = length;
    for (int i = 0; i < length; i++) {
        T->data[i].weight = weight[i];
        T->data[i].parent = 0;
        T->data[i].lchild = -1;
        T->data[i].rchild = -1;
    }
    return T;
}

int *search(HFtree *T) {
    int min = 1000000, secondmin = 1000000;
    int minindex, secondindex;
    for (int i = 0; i < T->length; i++) {
        if (T->data[i].parent == 0) {
            if (T->data[i].weight < min) {
                min = T->data[i].weight;
                minindex = i;
            }
        }
    }
    for (int i = 0; i < T->length; i++) {
        if (T->data[i].parent == 0 && i != minindex) {
            if (T->data[i].weight < secondmin) {
                secondmin = T->data[i].weight;
                secondindex = i;
            }
        }
    }
    int *p = (int *)malloc(sizeof(int) * 2);
    p[0] = minindex;
    p[1] = secondindex;
    return p;
}

HFtree *createTree(HFtree *T) {
    int *p;
    int min, secondmin;
    int n = T->length * 2 - 1;
    for (int i = T->length; i < n; i++) {
        p = search(T);
        min = p[0];
        secondmin = p[1];
        T->data[i].weight = T->data[min].weight + T->data[secondmin].weight;
        T->data[i].lchild = min;
        T->data[i].rchild = secondmin;
        T->data[min].parent = i;
        T->data[secondmin].parent = i;
        T->length++;
    }
    return T;
}

// Function to generate Huffman Codes for characters
void CreatHuffmanCode(TreeNode HT, TreeNode &HC, int n)
{
 HC = new char*[n + 1];//分配储存n个字符编码的编码表空间
 char *cd = new char[n];//分配临时存储字符编码的动态空间
 cd[n - 1] = '\0';//编码结束符
 for (int i = 1; i <= n; i++)//逐个求字符编码
 {
  int start = n - 1;//start 开始指向最后，即编码结束符位置
  int c = i;
  int f = HT[c].parent;//f指向结点c的双亲
  while (f != 0)//从叶子结点开始回溯，直到根结点
  {
   --start;//回溯一次，start向前指向一个位置
   if (HT[f].lchild == c) cd[start] = '0';//结点c是f的左孩子，则cd[start] = 0;
   else cd[start] = '1';//否则c是f的右孩子，cd[start] = 1
   c = f;
   f = HT[f].parent;//继续向上回溯
  }
  HC[i] = new char[n - start];//为第i个字符编码分配空间
  strcpy(HC[i], &cd[start]);//把求得编码的首地址从cd[start]复制到HC的当前行中
 }
 delete cd;
}

int main() {
    int a[52];
    FILE *fd = fopen("./text.txt", "rw");
    if (fd == NULL) {
        perror("无法打开文件");
        return 1;
    }

    char character;
    while ((character = getc(fd)) != EOF) {
        hashMap[character]++;
    }
    int i = 0;
    for (auto &pair : hashMap) {
        a[i++] = pair.second;
    }
    HFtree *root = init(a, i);
    TreeNode* HC = NULL;
    root = createTree(root);

    // Generate Huffman Codes
    HuffmanCode *huffmanCodes = (HuffmanCode *)malloc(sizeof(HuffmanCode) * root->length);
    CreatHuffmanCode(root,HC, root->length - 1);
 for (int i = 0; i < root->length; i++) {
        if (huffmanCodes[i].character != 0) {
            printf("Character: %c, Code: %s\n", huffmanCodes[i].character, huffmanCodes[i].code.c_str());
        }
    }

    // You can now use the huffmanCodes to encode and decode text.
    return 0;
}
