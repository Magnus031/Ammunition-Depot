#include <stdio.h>
#include <stdlib.h>
// Definition for a binary tree node.
struct TNode {
    int data;
    struct TNode* left;
    struct TNode* right;
};
typedef struct TNode* tree;
typedef tree Tree;
// Node structure for the queue used in BFS
struct QueueNode {
    struct TNode* data;
    struct QueueNode* next;
    struct QueueNode* pre;
};
// Queue structure
struct Queue {
    struct QueueNode* front, *rear;
};
Tree NewNode(int data){
    Tree T =(Tree)malloc(sizeof(struct TNode));
    T->data = data;
    T->left = NULL;
    T->right = NULL;
    return T;
}
Tree BuildTree(int in[],int post[],int N){
    if(N==0)
        return NULL;
    Tree root = NewNode(post[N-1]);//The root must be the last element of a postorder
    int i,j;
    for(i=0;i<N;i++){
        if(in[i]==post[N-1])
            break;
    }
    //Here i is the index of the inorder sequence;
    if (i + 1 < N) {
    for(j=0;j<N;j++){
        if(post[j]==in[i+1])
            break;
    }
    } else {
    j = N; // 将 j 设置为一个表示未找到元素的值
    }

    root->left=BuildTree(in,post,i);
    root->right=BuildTree(in+i+1,post+j,N-i-1);
    return root;
}
// Function to create a new queue node
struct QueueNode* createQueueNode(struct TNode* tnode) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = tnode;
    newNode->next = NULL;
    newNode->pre = NULL;
    return newNode;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to enqueue a tree node
void enqueue(struct Queue* queue, struct TNode* tnode) {
    struct QueueNode* newNode = createQueueNode(tnode);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    newNode->pre = queue->rear;
    queue->rear = newNode;
}
// Function to dequeue a tree node
struct TNode* dequeue(struct Queue* queue,int lefttoright) {
    if(lefttoright == 1){
        if (queue->front == NULL)
            return NULL;
        struct TNode* temp = queue->front->data;
        struct QueueNode* tempNode = queue->front;
        queue->front = queue->front->next;
        if (queue->front == NULL)
            queue->rear = NULL;
        free(tempNode);
        return temp;
    }else{
        if(queue->rear==NULL)
            return NULL;
        struct TNode* temp = queue->rear->data;
        struct QueueNode* tempNode = queue->rear;
        queue->rear = queue->rear->pre;
        if(queue->rear == NULL)
            queue->front = NULL;
        else
            queue->rear->next = NULL; 
        free(tempNode);
        return temp;
    }
}
// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == NULL||queue->rear==NULL;
}
// Function to perform level order traversal with zigzag ordering
void zigzagLevelOrder(tree root) {
    if (root == NULL)
        return;
    int count=0;
    // Create two stacks to store the nodes of current and next levels
    struct Queue* currentLevel = createQueue();
    struct Queue* nextLevel = createQueue();

    // Push the root node into the current level queue
    enqueue(currentLevel, root);

    // Variable to track the current traversal direction
    int leftToRight = 0;

    while (!isEmpty(currentLevel)) {
        struct TNode* temp = dequeue(currentLevel,leftToRight);

        if (temp) {
            // Print the current node's data
            if(count==0){
                printf("%d", temp->data);
                count++;
            }else{
                printf(" %d", temp->data);
            }
            // Enqueue the child nodes of the current node into the next level queue
                if (temp->left)
                    enqueue(nextLevel, temp->left);
                if (temp->right)
                    enqueue(nextLevel, temp->right);
        }
        // Move to the next level when the current level is empty
        if (isEmpty(currentLevel)) {
        leftToRight = 1 - leftToRight;

        // Check if there are nodes in the next level before swapping
        if (!isEmpty(nextLevel)) {
            struct Queue* tempQueue = currentLevel;
            currentLevel = nextLevel;
            nextLevel = tempQueue;
        }
    }
    }
}
void PrintTree(Tree T){
    if(T==NULL)
        return ;
    printf("%d ",T->data);
    PrintTree(T->left);
    PrintTree(T->right);
}
int main() {
    // Sample tree creation
    int N;
    scanf("%d",&N);
    int *in=(int*)malloc(sizeof(int)*(N+1));
    int *post=(int*)malloc(sizeof(int)*(N+1));
    for(int i=0;i<N;i++)
        scanf("%d",&in[i]);
    for(int i=0;i<N;i++)
        scanf("%d",&post[i]);
    Tree T=BuildTree(in,post,N);
    PrintTree(T);
    printf("\n");
    zigzagLevelOrder(T);
    return 0;
}
