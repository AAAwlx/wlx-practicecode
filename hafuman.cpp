#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define maxdouble 9999.9

struct huftree {
    char name;
    int weight;
    int lchild, rchild, parent;
};

struct hufcode {
    char bits[128];
    int start;
    char ch;
};

hufcode code[100];
huftree tree[200];
char huffmancode[1000];

int ch[256];
int leafnum = 0, hufnum = 0;

void myread() {
    std::ifstream file("SourceFile.txt");
    char c;
    while (file.get(c)) {
        if (ch[c] == 0)
            leafnum++;
        ch[c]++;
    }
    hufnum = 2 * leafnum;
}

void creattreehuffman(huftree tree[]) {
    int i, j, p1, p2;
    int least1, least2;

    i = 1;
    for (j = 0; j < 256; j++) {
        if (ch[j] == 0)
            continue;
        tree[i].name = j;
        tree[i].weight = ch[j];
        i++;
    }

    for (i = leafnum + 1; i <= hufnum - 1; i++) {
        p1 = 0;
        p2 = 0;
        least1 = least2 = 1000;
        for (j = 1; j < i; j++) {
            if (tree[j].parent == 0) {
                if (tree[j].weight < least1) {
                    least2 = least1;
                    least1 = tree[j].weight;
                    p2 = p1;
                    p1 = j;
                } else {
                    if (tree[j].weight < least2) {
                        least2 = tree[j].weight;
                        p2 = j;
                    }
                }
            }
        }
        tree[p1].parent = i;
        tree[p2].parent = i;
        tree[i].lchild = p1;
        tree[i].rchild = p2;
        tree[i].weight = tree[p1].weight + tree[p2].weight;
    }
    tree[hufnum - 1].parent = 0;
}

void creatcodehuffman(hufcode code[], huftree tree[]) {
    int i, cun, parent;
    hufcode buf;
    for (i = 1; i <= leafnum; i++) {
        buf.ch = tree[i].name;
        buf.start = leafnum;
        cun = i;
        parent = tree[i].parent;
        while (parent != 0) {
            buf.start--;
            if (tree[parent].lchild == cun)
                buf.bits[buf.start] = '0';
            else
                buf.bits[buf.start] = '1';
            cun = parent;
            parent = tree[parent].parent;
        }
        code[i] = buf;
    }
}

void writecodehuffman(hufcode code[], huftree tree[]) {
    int i, j, k, n = 0;
    std::ofstream output("DecodeFile.txt"); 
    char c;

    std::ifstream input("SourceFile.txt");
    while (input.get(c)) {
        for (j = 1; j <= leafnum; j++) {
            if (c == tree[j].name) {
                for (k = code[j].start; k < leafnum; k++) {
                    output << code[j].bits[k]; // 将编码写入输出文件
                    n++;
                }
            }
        }
    }
    
    input.close();
    output.close(); // 关闭输出文件
}

void printcodehuffman(hufcode code[]) {
    int i, j;
    std::ofstream output("CodeFile.txt"); 

    output << "字符序号   字符名称   \t 字符编码 \n";
    for (i = 1; i <= leafnum; i++) {
        output << "\t  " << i << " \t ";
        if (code[i].ch == '\n') {
            output << "\\n";
        } else {
            output << code[i].ch;
        }
        output << "\t\t-> \t ";
        for (j = code[i].start; j < leafnum; j++) {
            output << code[i].bits[j];
        }
        output << "\t \t \n";
    }

    output.close(); // 关闭输出文件
}

void transcodehuffman(hufcode code[], huftree tree[]) {
    int cun_node;
    char q;
    cun_node = hufnum - 1;
    std::ifstream input("codefile.txt");
    std::ifstream source("SourceFile.txt");
    std::ofstream output("Decodefile.txt");
    while (input.get(q)) {
        if (q == '0')
            cun_node = tree[cun_node].lchild;
        if (q == '1')
            cun_node = tree[cun_node].rchild;
        if ((tree[cun_node].lchild == 0) && (tree[cun_node].rchild == 0)) {
            if (code[cun_node].ch != source.get()) {
                std::cout << "CodeFile.txt 与 DecodeFile.txt 校验失败" << std::endl;
                return;
            }
            std::cout << code[cun_node].ch;
            output << code[cun_node].ch;
            cun_node = hufnum - 1;
        }
    }
    input.close();
    source.close();
    output.close();
    std::cout << "SourceFile.txt 与 DecodeFile.txt 校验成功!!!" << std::endl;
}

int main() {
    myread();
    std::cout << "SourceFile.txt  已读取!!!" << std::endl;
    creattreehuffman(tree);
    creatcodehuffman(code, tree);
    std::cout << "CodeFile.txt    已生成!!!" << std::endl;
    printcodehuffman(code);
    writecodehuffman(code, tree);
    std::cout << "DecodeFile.txt  已生成!!!" << std::endl;
    transcodehuffman(code, tree);

    return 0;
}