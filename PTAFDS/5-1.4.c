#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXS 8
#define MAXD 3
#define MAXB 5
#define Mask ((1<<(MAXD*MAXB))-1)

typedef char ElementType[MAXS+1];
enum EntryType {Legitimate,Empty};//2 states

struct HashEntry{
    ElementType Element;
    enum EntryType info;
};

struct HashTb1{
    int TableSize;
    struct HashEntry *Thecell;
};

typedef struct HashTb1 *HashTable;

HashTable InitializeTable(int TableSize){
    HashTable T =(HashTable)malloc(sizeof(struct HashTb1));
    T->TableSize = TableSize;
    T->Thecell = malloc(sizeof(struct HashEntry)*TableSize);
    while(TableSize){
        T->Thecell[--TableSize].info = Empty;
    }
    return T;
}


int Hash(char *key,int P){
    int h =0;
    while(*key!='\0'){
        h = (h<<MAXB)+(*key++ - 'A');
    }
    return (h&Mask)%P;
}

int Find(HashTable H,char *key){
    int inc,cnt=0;
    int Next,Pos;
    Next = Pos = Hash(key,H->TableSize);
    while((H->Thecell[Next].info!=Empty)&&strcmp(H->Thecell[Next].Element,key)){
        if(++cnt%2)//奇数次冲突
            inc = ((cnt+1)*(cnt+1))>>2;
        else //偶数次冲突
            inc = -(cnt*cnt)>>2;
        Next = Pos + inc;
        if(Next<0)
            Next+=H->TableSize;
        else if(Next>=H->TableSize)
            Next-=H->TableSize;
    }
    return Next;
}

void Insert(char* key,HashTable H){
    int Pos = Find(H,key);
    if(H->Thecell[Pos].info==Empty){
        H->Thecell[Pos].info=Legitimate;
        strcpy(H->Thecell[Pos].Element,key);
    }
    printf("%d",Pos);
}

int main(){
    int N,P,i;
    ElementType Key;
    HashTable H;
    scanf("%d %d",&N,&P);
    H = InitializeTable(P);
    scanf("%s",Key);
    Insert(Key,H);
    for(int i=1;i<N;i++){
        scanf("%s",Key);
        printf(" ");
        Insert(Key,H);
    }
    printf("\n");
    return 0;
}