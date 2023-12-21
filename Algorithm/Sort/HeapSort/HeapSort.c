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
Heap CreateHeap(int N);
Heap BuildMinHeap(int a[],int N);
int DeleteMin(Heap H);
int main(){
    int N;
    scanf("%d",&N);
    int *a=(int*)malloc(sizeof(int)*(N+1));
    for(int i=0;i<N;i++){
        scanf("%d",&a[i]);
    }
    Heap H= BuildMinHeap(a,N);
    for(int i=0;i<N;i++){
       printf("%d ",DeleteMin(H));
    }

}
Heap CreateHeap(int N){
    Heap H=(Heap)malloc(sizeof(struct HNode));
    H->size=N;
    H->num=0;
    H->array = (int*)malloc(sizeof(int)*(N+1));
    return H;
}
Heap BuildMinHeap(int a[],int N){
    Heap H=CreateHeap(N);
    int i,j;
    for(i=0;i<N;i++){
        for(j=++H->num;j>1&&H->array[j/2]>a[i];j=j/2)
            H->array[j]=H->array[j/2];
        H->array[j]=a[i];
    }
    return H;
}
int DeleteMin(Heap H){
    int min =  H->array[1];
    int temp = H->array[H->num--];
    int i,child;
    H->array[1]=temp;
    for(i = 1;i*2<=H->num;i=child){
        child = i*2;
        if(child!=H->num&&H->array[child]>H->array[child+1])
            child++;
        if(H->array[child]<temp)
            H->array[i]=H->array[child];
        else
            break;
    }
    H->array[i]=temp;
    return min;
}