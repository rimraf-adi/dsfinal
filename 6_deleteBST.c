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

Node* findMinNode(Node* root) {
    Node* current = root;
    
    while (current && current->left != NULL)
        current = current->left;
    
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;
    
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        
        Node* temp = findMinNode(root->right);
        
        root->data = temp->data;
        
        root->right = deleteNode(root->right, temp->data);
    }
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
    
    printf("BST before deletion (in-order traversal): ");
    inOrderTraversal(root);
    printf("\n");
    
    int keyToDelete = 30;
    root = deleteNode(root, keyToDelete);
    
    printf("BST after deleting %d (in-order traversal): ", keyToDelete);
    inOrderTraversal(root);
    printf("\n");
    
    keyToDelete = 50;
    root = deleteNode(root, keyToDelete);
    
    printf("BST after deleting %d (in-order traversal): ", keyToDelete);
    inOrderTraversal(root);
    printf("\n");
    
    freeTree(root);
    
    return 0;
}
