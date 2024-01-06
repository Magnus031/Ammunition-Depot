#include<stdio.h>
#include<stdlib.h>
int main(){
    int N;
    scanf("%d",&N);
    int *a=(int*)malloc(sizeof(int)*(N+1));
    for(int i=0;i<N;i++){
        scanf("%d",&a[i]);
    }
    if(N==1){
        printf("%d",0);
        return 0;
    }
    for(int i=0;i<N;i++){
        int min=a[i];
        int index=i;
        for(int j=i+1;j<N;j++){
            if(a[j]<min){
            min= a[j];
            index = j;
            }
        }
        int temp = a[index];
        a[index]=a[i];
        a[i]=temp;
    }
    int *b = (int*)malloc(sizeof(int)*(N));
    int sum=0;
    for(int i=0;i<N;i++)
        b[i]=0;
    for(int i=0;i<N/2;i++)
        b[i]=a[i*2]+a[i*2+1];
    int total=b[0];
    if(N%2==0)
        for(int i=0;i<N/2;i++){
            sum+=total;
            sum+=b[i+1];
            total+=b[i+1];
        }
    else{
        
    }
    printf("%d",sum);
    return 0;
}