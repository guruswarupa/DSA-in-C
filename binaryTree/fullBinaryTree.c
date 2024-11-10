#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node in a full binary tree
TreeNode* insert(TreeNode* root, int data) {
    // If the tree is empty, create the root node
    if (root == NULL) {
        return createNode(data);
    }

    // Use a queue for level order insertion
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*));  // Allocating memory for the queue
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        TreeNode* current = queue[front++];

        // Check if current node has no left child, if so, insert here
        if (current->left == NULL) {
            current->left = createNode(data);
            free(queue);  // Free the queue after insertion
            return root;
        }
        queue[rear++] = current->left;  // Add left child to queue

        // Check if current node has no right child, if so, insert here
        if (current->right == NULL) {
            current->right = createNode(data);
            free(queue);  // Free the queue after insertion
            return root;
        }
        queue[rear++] = current->right;  // Add right child to queue
    }
    
    free(queue);  // Free the queue memory
    return root;
}

// Function to perform inorder traversal
void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function to perform preorder traversal
void preorder(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Function to perform postorder traversal
void postorder(TreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Function to display the tree graphically
void displayTree(TreeNode* root, int space) {
    const int COUNT = 10; // Adjust the spacing for the tree representation
    if (root == NULL) return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    displayTree(root->right, space);

    // Print current node after space
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d", root->data);

    // Process left child
    displayTree(root->left, space);
}

// Function to free memory of the tree
void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Main function
int main() {
    TreeNode* root = NULL;

    // Insert nodes into the full binary tree
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 51);
    root = insert(root, 45);
    root = insert(root, 35);
    root = insert(root, 49);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);
    root = insert(root, 90);
    // Inorder traversal of the binary tree
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    // Preorder traversal of the binary tree
    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");

    // Postorder traversal of the binary tree
    printf("Postorder traversal: ");
    postorder(root);
    printf("\n");

    // Display the tree graphically
    printf("\nGraphical representation of the tree:\n");
    displayTree(root, 0);

    // Free the memory
    freeTree(root);

    return 0;
}
