

> 这里分享一个检查是否为BST的代码（镜像BST只需要反过来即可）

![image-20231219220118746](/Users/magnus/Library/Application Support/typora-user-images/image-20231219220118746.png)

> **输入输出案例**

1. Input:

   ![image-20231219220208533](/Users/magnus/Library/Application Support/typora-user-images/image-20231219220208533.png)

2. Output:

![image-20231219220234298](/Users/magnus/Library/Application Support/typora-user-images/image-20231219220234298.png)

#### 大致思路

输入 一个随机的序列 preorder sequence 我们要做的是判断它是否为一个BST的前序遍历序列

1) 建立堆栈

2) 其实就是找拐点 因为BST的preorder是先从往左边一直往下（有点BFS那味了）也就是我们一直push的过程
3) 当a[i]比当前Stack顶端的那个元素大的时候，说明开始在这个拐点（root）处的subtree的rightsubtree遍历了，那么接下来的先root=pop(S),此时的root是subtree的左叶，由于是BST，那么很自然的继续root=pop(S),可以得到此时子树的root，紧接着继续push,<font color=red>**这里有个关键点就是我们不再会有比当前root更小的元素了** </font>这是本题的关键，倘若在继续遍历的过程中 找到了比当前root更小的元素，则说明该序列无法构成某个BST的preorder sequence.

```C
#include<stdio.h>
#include<stdlib.h>
struct SNode{
  int top;
  int size;
  int *array;
};
typedef struct SNode *stack;
typedef stack Stack;
Stack CreatStack(int N);
int IsEmpty(Stack S);
int IsFull(Stack S);
void push(Stack S,int x);
int Check(int a[],int N);
void pop(Stack S);
int peek(Stack S);
int peek(Stack S){
  if(IsEmpty(S))
    return -1;
  return S->array[S->top];
}
void pop(Stack S){
  if(IsEmpty(S))
    return ;
  S->top--;
}
void push(Stack S,int x){
  if(IsFull(S))
    return ;
  S->array[++S->top]=x;
}
int IsFull(Stack S){
  return S->top==size-1;
}
int IsEmpty(Stack S){
  return S->top==-1;
}
Stack CreatStack(int N){
  Stack S = (Stack)malloc(sizeof(struct SNode));
  S->size = N;
  S->top=-1;
  S->array=(int*)malloc(sizeof(int)*(N+1));
}
//Here is the most important function
int Check(int a[],int N){
  int root=-1;
  Stack S=CreatStack(N);
  for(int i=0;i<N;i++){
    if(a[i]<root)
      return 0;
    
    while(!IsEmpty(S)&&a[i]>peek(S)){
      root=peek(S);
      pop(S);
    }
    
    push(S,x);
  }
  return 1;
}
```

#### 那么如何建立一个BST呢？

> 我们采取的是递归算法 具体如下:

```C
struct TNode;
struct TNode{
  int data;
  struct TNode *Left;
  struct TNode *Right;
};
typedef TNode *tree;
typedef tree Tree;
Tree NewNode(int data){
  Tree NewNode =(Tree)malloc(sizeof(struct TNode));
  NewNode->Left=NULL;
  NewNode->Right=NULL;
  NewNode->data=data;
  return NewNode;
}
Tree Build(int a[],int N){
  int preorder=0;
  return BuildUlti(a,&preorder,0,N-1,N);
}
Tree BuildUlti(int a[],int *preorder,int low,int high,int size){
  if(low>right||*preorder>=size)
    return NULL;
  
  Tree NewNode = NewNode(a[*preorder]);
  *preorder = *preorder +1;
  
  if(low==high)
    return NewNode;
  
  int i=0;
  for(i=low;i<=high;i++){
    if(a[i]>NewNode->data)
      break;
  }
  
  NewNode->Left = BuildUlti(a,preorder,*preorder,i-1,size);
  NewNode->Right = BuildUlti(a,preorder,i,high,size);
  return NewNode;
}
```

