#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

bool areIdentical(struct TreeNode* root1, struct TreeNode* root2) {
    if (root1 == NULL && root2 == NULL)
        return true;
    
    if (root1 == NULL || root2 == NULL)
        return false;
    
    return root1->data == root2->data && 
           areIdentical(root1->left, root2->left) && 
           areIdentical(root1->right, root2->right);
}

struct TreeNode* insertNode(struct TreeNode* root, int data) {
    if (root == NULL)
        return createNode(data);
    
    if (data == -1)
        return NULL;
        
    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);
    
    return root;
}

/*
struct TreeNode* buildTree() {
    int n, rootValue;
    struct TreeNode* root = NULL;
    
    printf("Enter the number of nodes in the tree: ");
    scanf("%d", &n);
    
    if (n <= 0)
        return NULL;
    
    printf("Enter the root value: ");
    scanf("%d", &rootValue);
    root = createNode(rootValue);
    
    printf("Enter the values for the remaining nodes (enter in level order):\n");
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

void freeTree(struct TreeNode* root) {
    if (root == NULL)
        return;
    
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void inOrderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;
    
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

int main() {
    /* Commented out user input
    printf("Building the first binary tree:\n");
    struct TreeNode* root1 = buildTree();
    
    printf("\nBuilding the second binary tree:\n");
    struct TreeNode* root2 = buildTree();
    */
    
    struct TreeNode* root1 = createNode(10);
    root1->left = createNode(5);
    root1->right = createNode(15);
    root1->left->left = createNode(3);
    root1->left->right = createNode(7);
    root1->right->left = createNode(12);
    
    struct TreeNode* root2 = createNode(10);
    root2->left = createNode(5);
    root2->right = createNode(15);
    root2->left->left = createNode(3);
    root2->left->right = createNode(7);
    root2->right->left = createNode(12);
    
    struct TreeNode* root3 = createNode(10);
    root3->left = createNode(5);
    root3->right = createNode(15);
    root3->left->left = createNode(3);
    root3->left->right = createNode(8);
    root3->right->left = createNode(12);
    
    printf("\nTree 1 in-order traversal: ");
    inOrderTraversal(root1);
    printf("\n");
    
    printf("Tree 2 in-order traversal: ");
    inOrderTraversal(root2);
    printf("\n");
    
    printf("Tree 3 in-order traversal: ");
    inOrderTraversal(root3);
    printf("\n\n");
    
    if (areIdentical(root1, root2))
        printf("Tree 1 and Tree 2 are identical.\n");
    else
        printf("Tree 1 and Tree 2 are not identical.\n");
    
    if (areIdentical(root1, root3))
        printf("Tree 1 and Tree 3 are identical.\n");
    else
        printf("Tree 1 and Tree 3 are not identical.\n");
    
    freeTree(root1);
    freeTree(root2);
    freeTree(root3);
    
    return 0;
}
