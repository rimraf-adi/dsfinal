#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node* root) {
    if (root == NULL)
        return 0;
    
    return 1 + max(height(root->left), height(root->right));
}

bool isBalanced(Node* root) {
    if (root == NULL)
        return true;
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    if (abs(leftHeight - rightHeight) <= 1 && 
        isBalanced(root->left) && 
        isBalanced(root->right))
        return true;
    
    return false;
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

void freeTree(Node* root) {
    if (root == NULL)
        return;
    
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void inOrderTraversal(Node* root) {
    if (root == NULL)
        return;
    
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

int main() {
    Node* balancedTree = createNode(10);
    balancedTree->left = createNode(5);
    balancedTree->right = createNode(15);
    balancedTree->left->left = createNode(3);
    balancedTree->left->right = createNode(7);
    balancedTree->right->left = createNode(12);
    
    Node* unbalancedTree = createNode(10);
    unbalancedTree->left = createNode(5);
    unbalancedTree->left->left = createNode(3);
    unbalancedTree->left->left->left = createNode(2);
    unbalancedTree->left->left->left->left = createNode(1);
    
    printf("Balanced tree in-order traversal: ");
    inOrderTraversal(balancedTree);
    printf("\n");
    
    printf("Unbalanced tree in-order traversal: ");
    inOrderTraversal(unbalancedTree);
    printf("\n\n");
    
    if (isBalanced(balancedTree))
        printf("The first tree is balanced.\n");
    else
        printf("The first tree is not balanced.\n");
    
    if (isBalanced(unbalancedTree))
        printf("The second tree is balanced.\n");
    else
        printf("The second tree is not balanced.\n");
    
    freeTree(balancedTree);
    freeTree(unbalancedTree);
    
    return 0;
}
