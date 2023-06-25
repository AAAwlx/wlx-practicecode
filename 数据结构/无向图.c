#include<stdio.h>
#include<stdlib.h>
typedef struct Graph
{
    char *vexs;
    int **arcs;
    int vexnum;
    int arcnum;
    /* data */
}Graph;
Graph* init(int vexnum)
{
    Graph *G=(Graph *)malloc(sizeof(Graph));
    G->vexs=(char *)malloc(sizeof(char)*vexnum);
    G->arcs=(int**)malloc(sizeof(int*)*vexnum);
    for(int i=0;i<vexnum;i++){
        G->arcs[i]=(int *)malloc(sizeof(int)*vexnum);
    }
    G->vexnum=vexnum;
    G->arcnum=0;
    return G;
}
void creat(Graph* G,char *vexs,int* arcs)
{
    for(int i=0;i<G->vexnum;i++){
        G->vexs[i]=vexs[i];
        for(int j=0;j<G->vexnum;j++){
            G->arcs[i][j]=*(arcs+i*G->vexnum+j);
            if (G->arcs[i][j]!=0){
                G->arcnum++;
            }
        }
    }
    G->arcnum/=2;
}
void DFS(Graph* G,int* visit,int index)
{
    printf("%c",G->vexs[index]);
    visit[index]=1;
    for(int i=0;i<G->vexnum;i++){
        if (G->arcs[index][i]==1&&visit[i]==0)
        {
            DFS(G,visit,i);
        }
    }
}
int main()
{
    Graph *G=init(5);
    int visit[5]={0};
    int arcs[5][5]={
        0,1,1,1,0,
        1,0,1,1,1,
        1,1,0,0,0,
        1,1,0,0,1,
        0,1,0,1,0
    };
    creat(G,"ABCDE",(int *)arcs);
    DFS(G,visit,0);
}