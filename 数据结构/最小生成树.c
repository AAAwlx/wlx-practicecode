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
typedef struct Edge{
    int weight;
    char vex;
}Edge;
Edge* initedge(Graph *G,int index)
{
    Edge *e=(Edge*)malloc(sizeof(Edge)*G->vexnum);
    for(int i=0;i<G->vexnum;i++){
        e[i].weight=G->arcs[index][i];
        e[i].vex=G->vexs[index];
    }
    return e;
}
int getminEdge(Edge *e,Graph* G){
    int index;
    int min=MAX;
    for(int i=0;i<G->vexnum;i++){
        if(e[i].weight!=0&&min>e[i].weight){
            min =e[i].weight;
            index=i;
        }
    }
    return index;
}
void prim(Graph *G,int index){
    int min;
    Edge *e=initedge(G,index);
    for(int i=0;i<G->vexnum-1;i++){
        min=getminEdge(e,G);
        printf("v%c->v%c,weight=%d\n",e[min].vex,G->vexs[min],e[min].weight);
        e[min].weight=0;
        for(int j=0;j<G->vexnum;j++){
            if(G->arcs[min][j]<e[j].weight)
            e[j].weight=G->arcs[min][j];
            e[j].vex=G->vexs[min];
        }
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
            if (G->arcs[i][j] != 0&&G->arcs[i][j]!=MAX)
            {
                G->arcnum++;
            }
        }
    }
    G->arcnum /= 2;
}
int main()
{
    Graph *G = init(6);
    int visit[6] = {0};
    int arcs[6][6] = {
        0,6,1,5,MAX,MAX,
        6,0,5,MAX,3,MAX,
        1,5,0,5,6,4,
        5,MAX,5,0,MAX,2,
        MAX,3,6,MAX,0,6,
        MAX,MAX,4,2,6,0
        };
    int c[6] = {0};
    creat(G, "123456", (int *)arcs);
    prim(G,0);
}