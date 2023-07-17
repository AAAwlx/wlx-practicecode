#include <stdio.h>
#include <stdlib.h>
#define MAX 101
typedef struct Graph
{
    char *vexs;
    int **arcs;
    int vexnum;
    int arcnum;
    /* data */
} Graph;

int a[MAX];
int r = -1, l = -1;
void Enter(int b)
{
    if (r == -1)
    {
        l += 1;
    }
    a[(r + 1) % MAX] = b;
    r++;
}
int Exit()
{
    int i = a[l];
    l++;
    return i;
}
int top()
{
    return a[r];
}
int Empty()
{
    if ((r == -1 && l == -1) || l > r)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
Graph *init(int vexnum)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->vexs = (char *)malloc(sizeof(char) * vexnum);
    G->arcs = (int **)malloc(sizeof(int *) * vexnum);
    for (int i = 0; i < vexnum; i++)
    {
        G->arcs[i] = (int *)malloc(sizeof(int) * vexnum);
    }
    G->vexnum = vexnum;
    G->arcnum = 0;
    return G;
}
void creat(Graph *G, char *vexs, int *arcs)
{
    for (int i = 0; i < G->vexnum; i++)
    {
        G->vexs[i] = vexs[i];
        for (int j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j] = *(arcs + i * G->vexnum + j);
            if (G->arcs[i][j] != 0)
            {
                G->arcnum++;
            }
        }
    }
    G->arcnum /= 2;
}
void DFS(Graph *G, int *visit, int index)
{
    printf("%c", G->vexs[index]);
    visit[index] = 1;
    for (int i = 0; i < G->vexnum; i++)
    {
        if (G->arcs[index][i] == 1 && visit[i] == 0)
        {
            DFS(G, visit, i);
        }
    }
}
void BFS(Graph *G, int *visit, int index)
{
    printf("%c", G->vexs[index]);
    visit[index] = 1;
    Enter(index);
    while (Empty())
    {
        int i = Exit();
        for (int j = 0; j < G->vexnum; j++)
        {
            if (G->arcs[i][j] == 1 && !visit[j])
            {
                printf("%c", G->vexs[j]);
                visit[j] = 1;
                Enter(j);
            }
        }
    }
}
int main()
{
    Graph *G = init(5);
    int visit[5] = {0};
    int arcs[5][5] = {
        0, 1, 1, 1, 0,
        1, 0, 1, 1, 1,
        1, 1, 0, 0, 0,
        1, 1, 0, 0, 1,
        0, 1, 0, 1, 0};
    int c[5] = {0};
    creat(G, "ABCDE", (int *)arcs);
    DFS(G,visit,0);
    BFS(G, c, 0);
}