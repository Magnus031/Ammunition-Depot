#include<stdio.h>
#include<stdlib.h>
#define Max 1001
struct TNode;
struct TNode{
    int data;
    struct TNode *Left;
    struct TNode *Right;
};
struct SNode;
struct SNode{
    int size;
    int top;
    int *array;
};
typedef struct SNode *stack;
typedef stack Stack;
typedef struct TNode *tree;
typedef tree Tree;
Tree NewsNode(int data);
void PrintTree(Tree T);
Tree BuildTree1(int a[],int N);
Tree BuildTree2(int a[],int N);
int Checkif1(int a[],int N);
int Checkif2(int a[],int N);
Stack CreatStack(int N);
int  Isempty(Stack S);
int IsFull(Stack S);
int peek(Stack S);
void push(Stack S,int x);
void pop(Stack S);
Tree BuildTreeR1(int a[],int *preindex,int low,int high,int size);
Tree BuildTreeR2(int a[],int *preindex,int low,int high,int size);
Tree SwapTree(Tree T);
int main(){
    int N;
    scanf("%d",&N);//input the number of the Nodes;
    int *check=(int*)malloc(sizeof(int)*(N+1));
    for(int i=0;i<N;i++)
        scanf("%d",&check[i]);
    int flag1=Checkif1(check,N);
    int flag2=Checkif2(check,N);
    if(flag1==0&&flag2==0){
        printf("NO\n");
        return 0;
    }else 
        printf("YES\n");
    if(flag1==1){
        Tree T=BuildTree1(check,N);
        PrintTree(T->Left);
        PrintTree(T->Right);
        printf("%d",T->data);
        return 0;
    }else if(flag2==1){//
        Tree T=BuildTree2(check,N);
        PrintTree(T->Left);
        PrintTree(T->Right);
        printf("%d",T->data);
        return 0;
    }
}
int Checkif1(int a[],int N){
    Stack S=CreatStack(N);
    int root=-1;
    for(int i=0;i<N;i++){
        if(a[i]<root)
            return 0;
        while(!Isempty(S)&&a[i]>peek(S)){
            root = peek(S);
            pop(S);
        }
        push(S,a[i]);
    }
    return 1;
}
int Checkif2(int a[],int N){
    Stack S=CreatStack(N);
    int root=100000;
    for(int i=0;i<N;i++){
        if(a[i]>root)
            return 0;
        while(!Isempty(S)&&a[i]<peek(S)){
            root = peek(S);
            pop(S);
        }
        push(S,a[i]);
    }
    return 1;
}
Tree NewsNode(int data){
    Tree NewNode =(Tree)malloc(sizeof(struct TNode));
    NewNode->data = data;
    NewNode->Left =NULL;
    NewNode->Right = NULL;
    return NewNode;
}
void PrintTree(Tree T){
    //Here is the function to print the postorder;
    if(T==NULL)
        return;
    PrintTree(T->Left);
    PrintTree(T->Right);
    printf("%d ",T->data);
}
Tree BuildTree1(int a[],int N){
    int preindex = 0;
    return BuildTreeR1(a,&preindex,0,N-1,N);
}
Stack CreatStack(int N){
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->size=N;
    S->top=-1;
    S->array = (int*)malloc(sizeof(int)*(N+1));
    return S;
}
int Isempty(Stack S){
    return S->top==-1;
}
int IsFull(Stack S){
    return S->top==S->size-1;
}
int peek(Stack S){
    if(Isempty(S))
        return -1;
    return S->array[S->top];
}
void push(Stack S,int x){
    if(IsFull(S))
        return ;
    S->array[++S->top]=x;
    return ;
}
void pop(Stack S){
    if(Isempty(S))
        return ;
    S->top--;
    return ;
}
Tree BuildTreeR1(int a[],int *preindex,int low,int high,int size){
    if(low>high||*preindex>=size)
        return NULL;
    Tree NewNode = NewsNode(a[*preindex]);
    *preindex = *preindex+1;
    if(low==high)
        return NewNode;
    int i;
    for(i=low;i<=high;i++){
        if(a[i]>NewNode->data)
            break;
    }
    NewNode->Left = BuildTreeR1(a,preindex,*preindex,i-1,size);
    NewNode->Right = BuildTreeR1(a,preindex,i,high,size);
    return NewNode;
}
Tree SwapTree(Tree T){
    Tree NewNode = NewsNode(0);
    if(T==NULL)
        return NULL;
    NewNode = T->Left;
    T->Left = T->Right;
    T->Right = NewNode;
    T->Left=SwapTree(T->Left);
    T->Right=SwapTree(T->Right);
    return T;
}
Tree BuildTree2(int a[],int N){
    int preindex = 0;
    return BuildTreeR2(a,&preindex,0,N-1,N);
}
Tree BuildTreeR2(int a[],int* preindex,int low,int high,int size){
    if(low>high||*preindex>=size)
        return NULL;
    Tree NewNode = NewsNode(a[*preindex]);
    *preindex = *preindex+1;
    if(low==high)
        return NewNode;
    int i;
    for(i=low;i<=high;i++){
        if(a[i]<NewNode->data)
            break;
    }
    NewNode->Left = BuildTreeR2(a,preindex,*preindex,i-1,size);
    NewNode->Right = BuildTreeR2(a,preindex,i,high,size);
    return NewNode;
}