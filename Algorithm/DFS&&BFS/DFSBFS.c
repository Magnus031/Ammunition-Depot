#include<stdio.h>
#include<stdlib.h>
#define MaxVertexNum 100
#define INFINITY 65535
#define MaxN 10
#define MaxSize 11
typedef int Vertex;
typedef int WeightType;
typedef struct ENode *PtrToENode;
int visit1[MaxVertexNum]={0};//visit[i]=0 represents that this node has not searched;
int visit2[MaxVertexNum]={0};
struct ENode{
    Vertex v1,v2;
};
typedef PtrToENode Edge;

typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;//The number of the Vertexs;
    int Ne;//The number of the Edges;
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph CreatGraph(int VertexNum){
    Vertex V,W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv=VertexNum;
    Graph->Ne=0;//initialization 0;

    for(V=0;V<Graph->Nv;V++){
        for(W=0;W<Graph->Nv;W++){
            Graph->G[V][W]=INFINITY;
        }
    }
    return Graph;
}

typedef struct QNode *Queue;
struct QNode{
    int value[MaxN];
    int front;
    int rear;
};

void InsertEdge(MGraph Graph,Edge E){
    Graph->G[E->v1][E->v2] = 1;
    //For the directed Graph
    Graph->G[E->v2][E->v1] = 1;
    //For the undirected Graph  
}

Queue CreatQueue(){
    Queue q = (Queue)malloc(sizeof(struct QNode));
    q->front=0;
    q->rear=0;
    return q;
}

void EnQueue(Queue Q,Vertex V){
    Q->value[Q->rear++]=V;
    if(Q->rear==MaxSize)
        Q->rear=Q->rear%MaxSize;//form a circle;
}

Vertex DeQueue(Queue Q){
    Vertex tmp =Q->value[Q->front++];
    if(Q->front==MaxSize)
        Q->front=Q->front%MaxSize;
    return tmp;
}

int Isempty(Queue Q){
    return Q->rear==Q->front;
}

MGraph BuildGraph(){
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv;
    scanf("%d",&Nv);
    Graph = CreatGraph(Nv);
    scanf("%d",&(Graph->Ne));
    if(Graph->Ne!=0){
        E=(Edge)malloc(sizeof(struct ENode));
        for(int i=0;i<Graph->Ne;i++){
            scanf("%d %d",&E->v1,&E->v2);
            InsertEdge(Graph,E);
        }
    }
    return Graph;
}

void DFS(MGraph Graph){
    //Depth First Search algorithm;
    int i=0;
    while(i<Graph->Nv){
        if(visit1[i]==0){
            printf("{");
            DFSR(Graph,i);
            printf(" }\n");
        }
        i++;
    }
}

void DFSR(MGraph Graph,Vertex V){
    printf(" %d",V);
    visit1[V]=1;
    for(int i=0;i<Graph->Nv;i++){
        if(!visit1[i]&&Graph->G[V][i]!=INFINITY){
            DFSR(Graph,i);
        }
    }
}

void BFS(MGraph Graph){
    //Breadth First Search algorithm;
    int i=0;
    for(i=0;i<Graph->Nv;i++){
        if(visit2[i]==0){
            printf("{ ");
            BFSR(Graph,i);
            printf(" }\n");
        }
    }
}

void BFSR(MGraph Graph,Vertex V){
    visit2[V]=1;
    printf("%d",V);
    Queue q=CreatQueue();//return an initialization queue;
    EnQueue(q,V);
    int tmp;
    while(!Isempty(q)){
        tmp=DeQueue(q);
        for(int i=0;i<Graph->Nv;i++){
            if(Graph->G[tmp][i]!=INFINITY &&!visit2[i]){
                printf(" %d",i);
                visit2[i]=1;
                EnQueue(q,i);
            }
        }
    }
}

int main(){
    MGraph Graph = BuildGraph();//initialization a Graph;
    DFS(Graph);
    BFS(Graph);
    return 0;
}