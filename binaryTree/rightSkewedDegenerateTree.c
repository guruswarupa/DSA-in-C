#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
typedef struct TreeNode {
    int data;
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
    newNode->right = NULL; // Only right child (degenerate tree)
    return newNode;
}

// Function to insert a node in a degenerate (right-skewed) tree
TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    
    // Insert only on the right to create a degenerate tree
    TreeNode* current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    current->right = createNode(data);
    
    return root;
}

// Function for inorder traversal (will behave like traversing a linked list)
void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->right);
        printf("%d ", root->data);
    }
}

// Function for preorder traversal (will visit nodes in the insertion order)
void preorder(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->right);
    }
}

// Function for postorder traversal (will behave like traversing a linked list in reverse order)
void postorder(TreeNode* root) {
    if (root != NULL) {
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Function to free memory of the degenerate tree
void freeTree(TreeNode* root) {
    while (root != NULL) {
        TreeNode* temp = root;
        root = root->right;
        free(temp);
    }
}

// Function to display the right-skewed tree graphically
void displayRightSkewedTreeGraphically(TreeNode* root, int space) {
    const int COUNT = 5; // Adjust the spacing for the tree representation (this value can be changed)

    // Base case: If the tree is empty
    if (root == NULL) {
        return;
    }

    // Increase the space between levels (since it's right-skewed, we only need to traverse right)
    space += COUNT;

    // Process the right child (right skewed, we don't have a left child to process)
    displayRightSkewedTreeGraphically(root->right, space);

    // Print current node after space
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");  // Print spaces for the visual indentation

    // Print the node value
    printf("%d", root->data);
}

// Main function
int main() {
    TreeNode* root = NULL;

    // Insert nodes into the degenerate (right-skewed) tree
    root = insert(root, 10);
    insert(root, 20);
    insert(root, 30);
    insert(root, 40);
    insert(root, 50);

    printf("Inorder traversal of the degenerate tree: ");
    inorder(root);
    printf("\n");

    printf("Preorder traversal of the degenerate tree: ");
    preorder(root);
    printf("\n");

    printf("Postorder traversal of the degenerate tree: ");
    postorder(root);
    printf("\n");

    printf("Display right-skewed tree structure graphically:\n");
    displayRightSkewedTreeGraphically(root, 0);

    // Free the memory
    freeTree(root);
    return 0;
}
