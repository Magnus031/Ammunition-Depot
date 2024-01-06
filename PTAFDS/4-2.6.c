#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 261
struct TNode;
struct TNode{
    char *value;
    Tree Left;//Left node is for the first child;
    Tree Right;//right node is for the next siblings;
};
typedef struct TNode *tree;
typedef tree Tree;
Tree CreateNode(char *p){
    Tree T =(Tree)malloc(sizeof(struct TNode));
    T->Left = NULL;
    T->Right = NULL;
    T->value=(char *)malloc(sizeof(char*)*(strlen(p)+1));
    strcpy(T->value,p);
    return T;
}
int main(){
    int N;
    scanf("%d",&N);
    Tree T = CreateNode("root");
    char str[M+1];
    for(int i=0;i<N;i++){
        scanf("%s",str);
        int j=0;
        while(str[j]!='\\'&&str[j]!='\0')
            j++;
        
    }
    return 0;
}