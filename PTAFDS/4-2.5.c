#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 1000
#define MAXM 20
#define MINX -10001
typedef enum { false, true } bool;
typedef struct heap* ph;
struct heap {
	int data[MAXN];
	int index;
};
ph Insert(ph H, int temp_x);
bool IsSiblings(ph H, int temp_x, int temp_x2);
bool IsChild(ph H, int temp_x2, int temp_x);
bool IsRoot(ph H, int temp_x);
bool IsParent(ph H, int temp_x, int temp_x2);
ph CreatMinHeap(int temp_x);
int Peek(ph H, int x);
int main()
{
	int N, M, i, temp_x, temp_x2;//N : n of x; M : n of case
	ph H = NULL;
	scanf("%d %d", &N, &M);
	for (i = 0; i < N; i++) {
		scanf("%d", &temp_x);
		H = Insert(H, temp_x);
	}
	char temp_case[101];
	for (i = 0; i < M; i++) {
		scanf("%d ", &temp_x);
		scanf("%s ", &temp_case);
		if (!strcmp(temp_case, "and")) {
			scanf("%d", &temp_x2);
			if (IsSiblings(H, temp_x, temp_x2)) printf("T\n");
			else printf("F\n");
			scanf("%s ", &temp_case);
			scanf("%s", &temp_case);
		}
		else {
			scanf("%s ", &temp_case);
			if (!strcmp(temp_case, "a")) {
				scanf("%s ", &temp_case);
				scanf("%s ", &temp_case);
				scanf("%d", &temp_x2);
			if(IsChild(H, temp_x2, temp_x)) printf("T\n");//x2 : dad ; x : child ;
				else printf("F\n");
			}
			else {
				scanf("%s ", &temp_case);
				if (!strcmp(temp_case, "root")) {
					if (IsRoot(H, temp_x)) printf("T\n");
					else printf("F\n");
				}
				else {
					scanf("%s ", &temp_case);
					scanf("%d ", &temp_x2);
					if(IsParent(H,temp_x, temp_x2)) printf("T\n");//x : dad ; x2 : child
					else printf("F\n");
				}
			}
		}
	}
	return 0;
}
ph Insert(ph H, int temp_x) {
	if (!H) return CreatMinHeap(temp_x);
	int i;
	for (i = ++H->index; H->data[i / 2] > temp_x; i /= 2) H->data[i] = H->data[i / 2];
	H->data[i] = temp_x;
	return H;
}
bool IsSiblings(ph H, int temp_x,int temp_x2) {
	if (Peek(H, temp_x) == 1 || Peek(H, temp_x2) == 1) return false;
	if ((!(Peek(H, temp_x) % 2) && Peek(H, temp_x2) == Peek(H, temp_x) + 1) || (!(Peek(H, temp_x2) % 2) && Peek(H, temp_x) == Peek(H, temp_x2) + 1)) return true;
	else return false;
}
bool IsChild(ph H, int dad,int son) {//x2 : dad ; x : child ;
	if (Peek(H, son) / 2 == Peek(H, dad)) return true;
	else return false;
}
bool IsRoot(ph H,int x) {
	return x == H->data[1] ? true : false;
}
bool IsParent(ph H, int dad,int son) {//x : dad ; x2 : child
	if (Peek(H, son) / 2 == Peek(H, dad)) return true;
	else return false;
}
ph CreatMinHeap(int temp_x) {
	ph H = (ph)malloc(sizeof(struct heap));
	H->index = 0;
	H->data[0] = MINX;
	H->data[++H->index] = temp_x;
	return H;
}
int Peek(ph H,int x) {
	int index = 0;
	while (H->data[++index] != x) ;
	return index;
}
