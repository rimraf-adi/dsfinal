#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} Node;

typedef struct QueueNode {
    Node* data;
    struct QueueNode* next;
} QNode;

typedef struct Queue {
    QNode* front;
    QNode* rear;
} Queue;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation failed\n");
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, Node* node) {
    QNode* newNode = (QNode*)malloc(sizeof(QNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = node;
    newNode->next = NULL;
    
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
        return;
    }
    
    queue->rear->next = newNode;
    queue->rear = newNode;
}

Node* dequeue(Queue* queue) {
    if (queue->front == NULL)
        return NULL;
    
    QNode* temp = queue->front;
    Node* node = temp->data;
    
    queue->front = queue->front->next;
    
    if (queue->front == NULL)
        queue->rear = NULL;
    
    free(temp);
    return node;
}

int isEmpty(Queue* queue) {
    return (queue->front == NULL);
}

void levelOrderTraversal(Node* root) {
    if (root == NULL)
        return;
    
    Queue* queue = createQueue();
    enqueue(queue, root);
    
    while (!isEmpty(queue)) {
        Node* current = dequeue(queue);
        printf("%d ", current->data);
        
        if (current->left != NULL)
            enqueue(queue, current->left);
        
        if (current->right != NULL)
            enqueue(queue, current->right);
    }
    
    free(queue);
}

Node* insert(Node* root, int data) {
    if (root == NULL)
        return createNode(data);
    
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    
    return root;
}

/*
Node* buildTree() {
    int n, rootValue;
    Node* root = NULL;
    
    printf("Enter the number of nodes in the tree: ");
    scanf("%d", &n);
    
    if (n <= 0)
        return NULL;
    
    printf("Enter the root value: ");
    scanf("%d", &rootValue);
    root = createNode(rootValue);
    
    printf("Enter the values for the remaining nodes:\n");
    
    for (int i = 1; i < n; i++) {
        int value;
        printf("Enter node %d: ", i+1);
        scanf("%d", &value);
        insert(root, value);
    }
    
    return root;
}
*/

void freeTree(Node* root) {
    if (root == NULL)
        return;
    
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node* root = NULL;
    
    // Creating a BST
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    
    printf("Level Order Traversal of BST: ");
    levelOrderTraversal(root);
    printf("\n");
    
    freeTree(root);
    
    return 0;
}
