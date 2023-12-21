#include<stdio.h>
#include<stdlib.h>
void QuickSort(int a[],int N); 
int Selected(int a[],int left,int right,int middle);
void swap(int *a,int *b);
int main(){
    int N;
    scanf("%d",&N);
    int *a=(int*)malloc(sizeof(int)*(N+1));
    for(int i=0;i<N;i++)
        scanf("%d",&a[i]);
    QuickSort(a,N);
    for(int i=0;i<N;i++){
        if(i==0)
            printf("%d",a[i]);
        else
            printf(" %d",a[i]);
    }
    return 0;
}
void QuickSort(int a[],int N){
    if(N==0||N==1)
        return ;
    int left = 0;
    int right = N-1;
    int Middle =(left+right)/2;
    int index = Selected(a,left,right,Middle);
    if(index!=right){
        swap(&a[index],&a[right]);
    }
    int i=0,j=N-2;
    while(i<=j){
        while(a[i]<a[right])
            i++;
        while(a[j]>a[right])
            j--;
        if(i <= j){
        swap(&a[i], &a[j]);
        i++;
        j--;
        }
    }
    swap(&a[i],&a[right]);
    QuickSort(a,i);
    QuickSort(a+i+1,N-i-1);
    return ;
}
int Selected(int a[],int left,int right,int middle){
    if(a[left]>a[right]){
            if(a[right]>a[middle])
                return right;
            else{//Here is the case that a[middle]>a[right]
                if(a[left]>a[middle]){
                    return middle;
                }else{
                    return left;
                }
            }
    }else{//Here is the case that a[left]<=a[right]
            if(a[left]>a[middle])
                return left;
            else{//a[left]<=a[middle]
                if(a[right]>a[middle])
                    return middle;
                else 
                    return right;
            }
    }
}
void swap(int *a,int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}