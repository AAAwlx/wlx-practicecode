#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    getchar(); // 读取换行符

    char vertices[n];
    for (int i = 0; i < n; i++) {
        scanf("%c", &vertices[i]);
    }
    getchar(); // 读取换行符

    // 初始化邻接矩阵和入度数组
    int tudejiedian[n][n];
    int xiabiao[n];
    for (int i = 0; i < n; i++) {
        xiabiao[i] = 0;
        for (int j = 0; j < n; j++) {
            tudejiedian[i][j] = 0;
        }
    }

    // 读取边信息并构建邻接矩阵和入度数组
    for (int i = 0; i < m; i++) {
        char v1, v2;
        scanf("<%c,%c>", &v1, &v2);
        int u = v1 - 'A', v = v2 - 'A'; // 将顶点字符转换为索引
        tudejiedian[u][v] = 1;
        xiabiao[v]++;
    }

    // 使用栈存储所有入度为0的顶点
    int myzhan[n], top = -1;
    for (int i = 0; i < n; i++) {
        if (xiabiao[i] == 0) {
            myzhan[++top] = i;
        }
    }

    // 进行拓扑排序
    int number = 0;
    while (top != -1) {
        int v = myzhan[top--];
        printf("%c", vertices[v]);
        number++;

        for (int i = 0; i < n; i++) {
            if (tudejiedian[v][i]) {
                xiabiao[i]--;
                if (xiabiao[i] == 0) {
                    myzhan[++top] = i;
                }
            }
        }
    }

    // 检查是否所有顶点都被排序了
    if (number != n) {
        printf("There are circles in the graph.\n");
    }

    return 0;
}