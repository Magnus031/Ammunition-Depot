#include<stdio.h>
#include<stdlib.h>
struct HNode;
struct HNode{
    int size;
    int num;
    int *array;
};
typedef struct HNode *heap;
typedef heap Heap;
Heap CreatHeap(int N);
Heap BuildMaxHeap(Heap H,int a[],int N);
int DeleteMax(Heap H);
int main(){
    int N,M;
    scanf("%d%d",&N,&M);
    int *check=(int*)malloc(sizeof(int)*(N+1));
    for(int i=0;i<N;i++){
        scanf("%d",&check[i]);
    }
    Heap H = CreatHeap(N);
    H=BuildMaxHeap(H,check,N);
    if(N>=M){
        for(int i=0;i<M;i++){
            int temp = DeleteMax(H);
            if(i==0)
                printf("%d",temp);
            else
                printf(" %d",temp);
        }
    }else{
            for(int i=0;i<N;i++){
                int temp = DeleteMax(H);
            if(i==0)
                printf("%d",temp);
            else
                printf(" %d",temp);
        }
    }
    return 0;
}
Heap CreatHeap(int N){
    Heap H = (Heap)malloc(sizeof(struct HNode));
    H->size = N;
    H->num=0;
    H->array = (int*)malloc(sizeof(int)*(N+1));
    H->array[0]=0;
    return H;
}
Heap BuildMaxHeap(Heap H,int a[],int N){
    int j;
    for(int i=0;i<N;i++){
        for(j=++H->num;j>1&&H->array[j/2]<a[i];j=j/2)
            H->array[j]=H->array[j/2];
        H->array[j]=a[i];
    }
    return H;
}
int DeleteMax(Heap H){
    if(H->num==1)
        return H->array[1];
    int temp=H->array[H->num--];
    int max = H->array[1];
    H->array[1]=temp;
    int i,child;
    for(i=1;i*2<=H->num;i=child){
        child=i*2;
        if(child!=H->num&&H->array[child]<H->array[child+1])
            child++;
        if(H->array[child]>temp)
            H->array[i]=H->array[child];
        else break;
    }
    H->array[i]=temp;
    return max;
}