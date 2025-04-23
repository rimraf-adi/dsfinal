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

Node* insert(Node* root, int data) {
    if (root == NULL)
        return createNode(data);
    
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    
    return root;
}

int countNodesWithTwoChildren(Node* root) {
    if (root == NULL)
        return 0;
    
    int count = 0;
    
    if (root->left != NULL && root->right != NULL)
        count = 1;
    
    return count + countNodesWithTwoChildren(root->left) + 
                  countNodesWithTwoChildren(root->right);
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
    Node* root = NULL;
    
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    
    printf("BST (in-order traversal): ");
    inOrderTraversal(root);
    printf("\n");
    
    int count = countNodesWithTwoChildren(root);
    printf("Number of nodes with exactly two children: %d\n", count);
    
    freeTree(root);
    
    return 0;
}
