#include<stdio.h>
#include<stdlib.h>
struct node
{
 int data;
 struct node * left;
 struct node * right;
};
typedef struct node * Bintree;
struct heap
{
 Bintree * d;
 int size;
};
typedef struct heap * Heap;
Heap Insert(Heap H, Bintree B);//向最小堆内插入元素
Bintree Delete(Heap H);//删除最小堆内最小的元素
Bintree Create(Heap H);//创建哈夫曼树的函数
void Sum(Bintree B);//求最少花费的函数
int sum = 0;//记录结果
int main()
{
 int n;
 scanf("%d", &n);
 int i;
 Bintree B;
 Heap H;
 H = (Heap)malloc(sizeof(struct heap));
 H->d = (Bintree *)malloc((n+1) * sizeof(Bintree));
 for (i = 0; i <= n; i++)
 {
  H->d[i] = (Bintree)malloc(sizeof(struct node));
 }
 H->d[0]->data = -100;//岗哨
 H->d[0]->left = H->d[0]->right = NULL;
 H->size = 0;
 for (i = 1; i <= n; i++)
 {
  B = (Bintree)malloc(sizeof(struct node));
  scanf("%d", &B->data);
  B->left = B->right = NULL;
  H = Insert(H, B);
 }
 Bintree HF;
 HF = Create(H);
 Sum(HF);
 printf("%d", sum);
 return 0;
}
//向最小堆内插入元素
Heap Insert(Heap H, Bintree B)
{
 int i = ++H->size;
 while (B->data < H->d[i / 2]->data)
 {
  H->d[i] = H->d[i / 2];
  i = i / 2;
 }
 H->d[i] = B;
 return H;
}
//删除最小堆内最小的元素
Bintree Delete(Heap H)
{
 Bintree B;
 B = H->d[1];
 int i = H->size;
 int j = 2;
 while (j<i)
 {
  if (H->d[j]->data > H->d[j + 1]->data)
  {
   j = j + 1;
  }
  if (H->d[j]->data < H->d[i]->data)
  {
   H->d[j / 2] = H->d[j];
  }
  else { break; }
  j = 2 * j;
 }
 H->d[j/2] = H->d[i];
 H->size--;
 return B;
}
//创建哈夫曼树的函数
Bintree Create(Heap H)
{
 Bintree p1, p2,p;
 while (H->size != 1)//直至最小堆内仅剩一个元素，该元素内存的是哈夫曼树的根结点地址
 {
  p = (Bintree)malloc(sizeof(struct node));
  p1 = Delete(H);
  p2 = Delete(H);
  p->data = p1->data + p2->data;
  p->left = p1;
  p->right = p2;
  H = Insert(H, p);
 }
 return H->d[H->size];
}
//求最少花费的函数
//前序遍历，将所有非叶结点的data值求和，即为所求值
void Sum(Bintree B)
{
 if (B != NULL)
 {
  if (B->left != NULL && B->right != NULL) { sum = sum + B->data; }
  Sum(B->left);
  Sum(B->right);
 }
}