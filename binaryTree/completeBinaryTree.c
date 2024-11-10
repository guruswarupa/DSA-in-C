#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function declarations
TreeNode* createNode(int data);
TreeNode* insert(TreeNode* root, int data);
TreeNode* findLastNode(TreeNode* root);
TreeNode* deleteNode(TreeNode* root, int data);
TreeNode* search(TreeNode* root, int data);  // Forward declaration for search function
void inorder(TreeNode* root);
void preorder(TreeNode* root);
void postorder(TreeNode* root);
void displayTree(TreeNode* root, int space);
void freeTree(TreeNode* root);

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

// Function to insert a node in the binary tree as a complete binary tree
TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    // Use a queue to insert the node in level order
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*)); // Allocate memory for the queue
    int front = 0, rear = 0;
    queue[rear++] = root;

    // Traverse the tree in level order
    while (front < rear) {
        TreeNode* current = queue[front++];

        // Check left child
        if (current->left != NULL) {
            queue[rear++] = current->left;
        } else {
            current->left = createNode(data);
            free(queue); // Free the queue memory before returning
            return root;
        }

        // Check right child
        if (current->right != NULL) {
            queue[rear++] = current->right;
        } else {
            current->right = createNode(data);
            free(queue); // Free the queue memory before returning
            return root;
        }
    }
    
    free(queue); // Free the queue memory if no position found
    return root;
}

// Function to find the last node in the tree (the rightmost node at the lowest level)
TreeNode* findLastNode(TreeNode* root) {
    if (root == NULL) return NULL;

    // Use a queue to traverse the tree in level-order to find the last node
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*)); // Allocate memory for the queue
    int front = 0, rear = 0;
    queue[rear++] = root;

    TreeNode* lastNode = NULL;

    while (front < rear) {
        TreeNode* current = queue[front++];
        lastNode = current;

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }

    free(queue); // Free the queue memory before returning
    return lastNode;
}

// Function to delete a node from the binary tree while maintaining completeness
TreeNode* deleteNode(TreeNode* root, int data) {
    if (root == NULL) return NULL;

    // Use a queue to find the node to be deleted and the last node
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*)); // Allocate memory for the queue
    int front = 0, rear = 0;
    queue[rear++] = root;
    TreeNode* targetNode = NULL;

    while (front < rear) {
        TreeNode* current = queue[front++];
        
        if (current->data == data) {
            targetNode = current;
        }

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }

    // If target node is found
    if (targetNode) {
        TreeNode* lastNode = findLastNode(root);

        // Replace the target node with the last node
        targetNode->data = lastNode->data;

        // Delete the last node
        TreeNode** queue2 = (TreeNode**)malloc(100 * sizeof(TreeNode*));
        int front2 = 0, rear2 = 0;
        queue2[rear2++] = root;

        TreeNode* parent = NULL;
        while (front2 < rear2) {
            parent = queue2[front2++];
            if (parent->left == lastNode) {
                parent->left = NULL;
                break;
            } else if (parent->right == lastNode) {
                parent->right = NULL;
                break;
            }
            if (parent->left != NULL) queue2[rear2++] = parent->left;
            if (parent->right != NULL) queue2[rear2++] = parent->right;
        }

        free(queue2); // Free the second queue
    }

    free(queue); // Free the queue memory
    return root;
}

// Function to search for a node in the binary tree
TreeNode* search(TreeNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    TreeNode* found = search(root->left, data);
    if (found) return found;

    return search(root->right, data);
}

// Function for inorder traversal
void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function for preorder traversal
void preorder(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Function for postorder traversal
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

    // Insert nodes into the binary tree
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 10);
    insert(root, 51);
    insert(root, 45);
    insert(root, 35);
    insert(root, 49);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder traversal of the binary tree: ");
    inorder(root);
    printf("\n");

    printf("Preorder traversal of the binary tree: ");
    preorder(root);
    printf("\n");

    printf("Postorder traversal of the binary tree: ");
    postorder(root);
    printf("\n");

    // Display the tree graphically
    printf("\nGraphical representation of the binary tree:\n");
    displayTree(root, 0);

    // Search for a node
    int key = 4;
    TreeNode* found = search(root, key);
    if (found != NULL) {
        printf("\nKey %d found in the binary tree.\n", key);
    } else {
        printf("\nKey %d not found in the binary tree.\n", key);
    }

    // Delete a node
    root = deleteNode(root, 20);
    printf("Inorder traversal after deleting 20: ");
    inorder(root);
    printf("\n");

    // Free the memory
    freeTree(root);
    return 0;
}
