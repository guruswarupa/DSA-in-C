#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
} TreeNode;

// Function to create a new node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL; // Only left child (left-skewed degenerate tree)
    return newNode;
}

// Function to insert a node in a left-skewed degenerate tree
TreeNode* insertLeftSkewed(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    // Insert only on the left to create a left-skewed degenerate tree
    TreeNode* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    current->left = createNode(data);

    return root;
}

// Function to perform inorder traversal
void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
    }
}

// Function to perform preorder traversal
void preorder(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
    }
}

// Function to perform postorder traversal
void postorder(TreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        printf("%d ", root->data);
    }
}

// Function to display the left-skewed tree graphically (vertically)
void displayLeftSkewedTreeGraphically(TreeNode* root, int space) {
    const int COUNT = 5; // Adjust the spacing for the tree representation

    // Base case: If the tree is empty
    if (root == NULL) {
        return;
    }

    // Print current node first (so the tree grows downwards)
    printf("\n");
    for (int i = 0; i < space; i++) {
        printf(" ");  // Print spaces for indentation
    }
    printf("%d", root->data);  // Print the current node value

    // Now process the left child (go deeper into the tree)
    displayLeftSkewedTreeGraphically(root->left, space + COUNT);
}

// Function to free memory of the left-skewed tree
void freeLeftSkewedTree(TreeNode* root) {
    while (root != NULL) {
        TreeNode* temp = root;
        root = root->left;
        free(temp);
    }
}

// Main function
int main() {
    TreeNode* root = NULL;

    // Insert nodes into the left-skewed degenerate tree
    root = insertLeftSkewed(root, 10);
    insertLeftSkewed(root, 20);
    insertLeftSkewed(root, 30);
    insertLeftSkewed(root, 40);
    insertLeftSkewed(root, 50);

    // Inorder traversal of the left-skewed tree
    printf("Inorder traversal of the left-skewed tree: ");
    inorder(root);
    printf("\n");

    // Preorder traversal of the left-skewed tree
    printf("Preorder traversal of the left-skewed tree: ");
    preorder(root);
    printf("\n");

    // Postorder traversal of the left-skewed tree
    printf("Postorder traversal of the left-skewed tree: ");
    postorder(root);
    printf("\n");

    // Display the left-skewed tree structure graphically
    printf("\nGraphical representation of the left-skewed tree:\n");
    displayLeftSkewedTreeGraphically(root, 0);

    // Free the memory
    freeLeftSkewedTree(root);
    return 0;
}
