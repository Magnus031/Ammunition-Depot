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
Heap BuildminHeap(Heap H,int a[],int N);
int Deletemin(Heap H);
int main(){
    int N;
    scanf("%d",&N);
    int *a=(int*)malloc(sizeof(int)*(N+1));
    int **b=(int*)malloc(sizeof(int)*(N+1));
    for(int i=0;i<N;i++)
        scanf("%d",&a[i]);//input the ages of the worker;
    Heap H=CreatHeap(N);
    H=BuildminHeap(H,a,N);
    int last =-1;
    int count=-1;
    for(int i=0;i<N;i++){
        int temp = Deletemin(H);
        if(temp!=last){
            b[++count]=(int*)malloc(sizeof(int)*2);
            b[count][0]=temp;
            b[count][1]=1;
        }else{
            b[count][1]++;
        }
        last = temp;
    }
    for(int i=0;i<count+1;i++){
        printf("%d:%d\n",b[i][0],b[i][1]);
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
Heap BuildminHeap(Heap H,int a[],int N){
    int j;
    for(int i=0;i<N;i++){
        for(j=++H->num;j>1&&H->array[j/2]>a[i];j=j/2)
            H->array[j]=H->array[j/2];
        H->array[j]=a[i];
    }
    return H;
}
int Deletemin(Heap H){
    if(H->num==1)
        return H->array[1];
    int temp=H->array[H->num--];
    int min = H->array[1];
    H->array[1]=temp;
    int i,child;
    for(i=1;i*2<=H->num;i=child){
        child=i*2;
        if(child!=H->num&&H->array[child]>H->array[child+1])
            child++;
        if(H->array[child]<temp)
            H->array[i]=H->array[child];
        else break;
    }
    H->array[i]=temp;
    return min;
}