#include<stdio.h>
#include<stdlib.h>
int main(){
    int N,P;
    scanf("%d%d",&N,&P);
    int *a =(int*)malloc(sizeof(int)*P);
    int *b =(int*)malloc(sizeof(int)*N);
    for(int i=0;i<P;i++)a[i]=-1;
    for(int i=0;i<N;i++){
        scanf("%d",&b[i]);
        int temp = b[i]%P;
        int j=0;
        if(a[temp]==b[i]){
            b[i]=temp;
            continue;
        }
        while(a[temp]!=-1&&j<P&&(a[temp]!=b[i])){
                j++;
                temp=(temp+1)%P;
        }
        a[temp]=b[i];
        b[i]=temp;
        
    }
    for(int i=0;i<N;i++){
        if(i==0)
            printf("%d",b[i]);
        else 
            printf(" %d",b[i]);
    }
    return 0;
}