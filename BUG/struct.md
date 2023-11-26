# 结构体的小bug
> This is a so simple bug that I have debugged for around 2 hours!🥺

## 描述
<b>这个bug是在我学图的时候出现的，在完成一个 DPS和BPS的算法设计的时候</b>

```C
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
```
看起来这是个很简单的函数，我看了十几遍，就是没有看见问题在哪？但事实上 问题出在了动态分配内存的<b>sizeof</b>那里。

### 一组定义
```C
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;//The number of the Vertexs;
    int Ne;//The number of the Edges;
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;
```
其实`Graph = (MGraph)malloc(sizeof(MGraph))`和`Graph = (MGraph)malloc(sizeof(struct GNode))`两个是有区别的，区别在sizeof函数对于`MGraph`是对于返回指针大小，而`struct GNode`返回的是结构体的大小。
> 另外，其实这里有个地方值得注意的是 为什么malloc前面的`(MGraph)` 因为这里是强制类型转化！使得动态分配出来的变量是`MGraph`类型！