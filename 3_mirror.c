#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} Node;

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

void mirror(Node* root) {
    if (root == NULL)
        return;
    
    Node* temp;
    
    mirror(root->left);
    mirror(root->right);
    
    temp = root->left;
    root->left = root->right;
    root->right = temp;
}

Node* createMirrorTree(Node* root) {
    if (root == NULL)
        return NULL;
    
    Node* newNode = createNode(root->data);
    
    newNode->right = createMirrorTree(root->left);
    newNode->left = createMirrorTree(root->right);
    
    return newNode;
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
    printf("To represent NULL nodes, enter -1\n");
    
    for (int i = 1; i < n; i++) {
        int value;
        printf("Enter node %d: ", i+1);
        scanf("%d", &value);
        if (value != -1) {
            insertNode(root, value);
        }
    }
    
    return root;
}
*/

void inOrderTraversal(Node* root) {
    if (root == NULL)
        return;
    
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

void freeTree(Node* root) {
    if (root == NULL)
        return;
    
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node* originalTree = createNode(1);
    originalTree->left = createNode(2);
    originalTree->right = createNode(3);
    originalTree->left->left = createNode(4);
    originalTree->left->right = createNode(5);
    originalTree->right->left = createNode(6);
    originalTree->right->right = createNode(7);
    
    printf("Original tree (in-order traversal): ");
    inOrderTraversal(originalTree);
    printf("\n");
    
    Node* mirrorTree = createMirrorTree(originalTree);
    
    printf("Mirror tree (in-order traversal): ");
    inOrderTraversal(mirrorTree);
    printf("\n");
    
    printf("Mirroring the original tree in-place...\n");
    mirror(originalTree);
    
    printf("Original tree after mirroring (in-order traversal): ");
    inOrderTraversal(originalTree);
    printf("\n");
    
    freeTree(originalTree);
    freeTree(mirrorTree);
    
    return 0;
}
