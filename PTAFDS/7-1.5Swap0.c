#include<stdio.h>
#include<stdlib.h>
int getindex(int a[],int N,int x);
void QuickSort(int a[], int b[], int left, int right);//Here b[] is for the index-array;
int Selected(int a[],int b[],int left,int right,int middle);
void swap(int *a,int *b);
int main(){
    int N;
    scanf("%d",&N);
    int *a=(int *)malloc(sizeof(int)*(N+1));
    int *table=(int*)malloc(sizeof(int)*(N+1));
    for(int i=0;i<N;i++)
        scanf("%d",&a[i]);
    for(int i=0;i<N;i++){
        table[i]=i;
    }
    QuickSort(a,table,0,N-1);
    int count =0;
    int current = getindex(a,N,0);
    int next= table[current];
    while(current!=next){
        //Here is the case that 0 is not in the index 0 place;
        table[current]=current;
        current = next;
        next = table[next];
        if(current==next)
            break;
        else{
            count++;
        }
    }
    for(int i=0;i<N;i++){
        if(i==table[i])
            continue;
        else{
            current = i;
            next = table[i];
            count+=2;
            while(current!=next){
                table[current]=current;
                current = next;
                next = table[next];
                if(current == next)
                    break;
                else{
                    count++;
                }
            }
        }
    }
    printf("%d",count);
    return 0;
}
int getindex(int a[],int N,int x){
    for(int i=0;i<N;i++){
        if(a[i]==x)
            return i;
    }
    return 0;
}
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Selected(int a[], int b[], int left, int right, int middle) {
    if (a[b[left]] > a[b[right]]) {
        if (a[b[right]] > a[b[middle]]) {
            return right;
        } else { // Here is the case that a[middle] > a[right]
            if (a[b[left]] > a[b[middle]]) {
                return middle;
            } else {
                return left;
            }
        }
    } else { // Here is the case that a[left] <= a[right]
        if (a[b[left]] > a[b[middle]]) {
            return left;
        } else { // a[left] <= a[middle]
            if (a[b[right]] > a[b[middle]]) {
                return middle;
            } else {
                return right;
            }
        }
    }
}

void QuickSort(int a[], int b[], int left, int right) {
    // Base case
    if (left >= right) {
        return;
    }

    int middle = (left + right) / 2;
    int index = Selected(a, b, left, right, middle);

    if (index != right) {
        swap(&b[index], &b[right]);
    }

    int i = left, j = right - 1;
    while (i <= j) {
        while (a[b[i]]<a[b[right]]) {
            i++;
        }
        while (a[b[j]]>a[b[right]]) {
            j--;
        }
        if (i <= j) {
            swap(&b[i],&b[j]);
            i++;
            j--;
        }
    }

    swap(&b[i], &b[right]);
    QuickSort(a, b, left, i - 1);
    QuickSort(a, b, i + 1, right);
}
