#include <iostream>
#include <cstring>
#include <stdio.h> 
using namespace std;

typedef struct HTNode
{
    int weight;
    int parent;
    int lchild;
    int rchild;
}HTNode,*HuffmanTree;

//封装最小的权和次小的全 
typedef struct
{
    int p1,p2;
}*MinCode;

static char N[100];
typedef char **HuffmanCode;//Huffman编码 

//当输入1个结点时，提示输出错误 
void Error(const char *message)
{
    cerr<<"Errors: "<<message<<endl;
    exit(1);//非return,如果return 会造成main函数HT[i]无值
}

//
MinCode Select(HuffmanTree HT,int n)
{
    int Min=0x3f3f,p1=1,p2=1;
    //找出权值weight最小的结点，下标保存在p1中 
    for(int i=1;i<=n;++i)
        if(HT[i].weight<Min&&HT[i].parent==0)
        {
            Min=HT[i].weight;
            p1=i;
        }
    //找出权值weight次小的结点，下标保存在p1中     
    int SecMin=0x3f3f;
    for(int i=1;i<=n;++i)
        if((HT[i].weight<SecMin)&&(i!=p1)&&(HT[i].parent==0))
        {
            SecMin=HT[i].weight;
            p2=i;
        }
    
    //封装进结构体中 
    MinCode Code;
    Code->p1=p1;
    Code->p2=p2;
    
    return Code;
}

//构造HUffman树HT，编码存放在HC中，w为权值，n为结点个数
HuffmanCode huffman_codeing(HuffmanTree &HT,HuffmanCode HC,int *w,int n)
{
    if(n<=1)
        Error("Code to samll.");
        
    int m=2*n-1;
    HT=new HTNode[m+1];//第0个空间不用，故申请m+1个空间 
    
    //初始化n个叶子结点 
    HuffmanTree p=HT;
    int i=1;
    for(++p,++w;i<=n;++i,++p,++w)
    {
        p->weight=*w;
        p->lchild=p->rchild=p->parent=0;
    }
    //n-1个非叶子结点初始化
    for(;i<=m;++i,++p) 
        p->weight=p->parent=p->lchild=p->rchild=0;
    
    //构造Huffman树 
    MinCode Min;
    int p1=0,p2=0;
    for(i=n+1;i<=m;++i) 
    {
        Min=Select(HT,i-1);//找出最小和次小连个结点 
        p1=Min->p1;//最小下标 
        p2=Min->p2;//次小下标 
        HT[p1].parent=i;
        HT[p2].parent=i;//最小下标和次小下标同一树，双亲相同 
        HT[i].lchild=p1;//i结点的左孩子 
        HT[i].rchild=p2;//i结点的右孩子 
        HT[i].weight=HT[p1].weight+HT[p2].weight;//i结点的权值 
    }
    
    //打印Huffman树 
    printf("HT  List:\n");
    printf("Number\t\tweight\t\tparent\t\tlchild\t\trchild\n");
    for(int i=1;i<=m;i++)
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
    
    //从叶子结点到根结点求每个字符的Huffman编码
    HC=new char*[n+1];
    //为Huffman编码动态分配空间 
    char *cd=new char[n];
    cd[n-1]='\0';//3个结点的Huffman编码最长为2 
    
    //求叶子结点的Huffman编码
    for(int i=1;i<=n;++i) 
    {
        int start=n-1;
        //左子树为0右子树为1，从最下边1号开始往上编码(逆序存放)，然后2号结点，3号...
        for(int c=i,f=HT[i].parent;f>0;c=f,f=HT[f].parent) 
            if(HT[f].lchild==c)
                cd[--start]='0';
            else
                cd[--start]='1';
            
        //为第i个字符分配空间
        HC[i]=new char[n-start];
        //将Huffman编码复制到HC 
        strcpy(HC[i],&cd[start]);
    }
    free(cd);
    return HC;
}

//译码
void huffman_translate_codeing(HuffmanTree HT,int n,char *ch) 
{
    int m=2*n-1,i,j=0;
    cout<<"After Translation:"<<endl;
    
    while(ch[j]!='\0')//要译码的串
    {
        i=m;
        while(HT[i].lchild!=0&&HT[i].rchild!=0)//从顶部向下找 
        {
            if(ch[j]=='0')//0往左走
                i=HT[i].lchild;
            else//1往右走 
                i=HT[i].rchild;
            
            ++j;
        }
        cout<<N[i-1];
    } 
    cout<<endl;
}

int main()
{
    cout<<"Input N(char):";
    cin.getline(N,100,'\n');
    cin.clear();//清空输入流 
    cin.sync();
    
    int len=strlen(N);
    int *w=new int[len+1];
    
    cout<<"Enter weight:"<<endl;
    for(int i=1;i<=len;++i)
    {
        cout<<"w["<<i<<"]=";
        cin>>w[i];
    }
    cin.clear();//清空输入流 
    cin.sync();
    
    HuffmanTree HT=NULL;
    HuffmanCode HC=NULL;
    HC=huffman_codeing(HT,HC,w,len);

    //输出Huffman编码
    cout<<"HuffmanCode:" <<endl;
    printf("Number\t\tWeight\t\tCode\n");
    for(int i=1;i<=len;i++)
    {
        printf("%c\t\t%d\t\t%s\n",N[i-1],w[i],HC[i]);
    }
    cin.clear();//清空输入流 
    cin.sync();
    
    //译码
    char tran[100];
    cout<<"Input HuffmanTranslateCodeing(like 101010):";
    cin.getline(tran,100,'\n');
    huffman_translate_codeing(HT,len,tran);
    
    free(HT);
    free(HC);
    return 0;
}
