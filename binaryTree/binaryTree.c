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

// Function to insert a node in the binary tree in level order
void insert(TreeNode** root, int data) {
    TreeNode* newNode = createNode(data);
    if (*root == NULL) {
        *root = newNode;
        return;
    }

    // Level order traversal to find an empty spot
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*)); // Using a simple queue for level order traversal
    int front = 0, rear = 0;
    queue[rear++] = *root;

    while (front < rear) {
        TreeNode* temp = queue[front++];

        if (temp->left == NULL) {
            temp->left = newNode;
            break;
        } else {
            queue[rear++] = temp->left;
        }

        if (temp->right == NULL) {
            temp->right = newNode;
            break;
        } else {
            queue[rear++] = temp->right;
        }
    }
    free(queue);
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

// Function to search for a node in the binary tree
TreeNode* search(TreeNode* root, int data) {
    if (root == NULL) {
        return NULL;
    }

    // Use level order traversal to find the data
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*));
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        TreeNode* temp = queue[front++];

        if (temp->data == data) {
            free(queue);
            return temp;
        }

        if (temp->left != NULL) {
            queue[rear++] = temp->left;
        }
        if (temp->right != NULL) {
            queue[rear++] = temp->right;
        }
    }

    free(queue);
    return NULL; // If the data is not found
}

// Function to display the tree graphically
void displayTree(TreeNode* root, int space) {
    const int COUNT = 10; // Adjust the spacing for the tree representation
    if (root == NULL) return;

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
    insert(&root, 1);
    insert(&root, 2);
    insert(&root, 3);
    insert(&root, 4);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 7);

    printf("Inorder traversal of the binary tree: ");
    inorder(root);
    printf("\n");

    printf("Preorder traversal of the binary tree: ");
    preorder(root);
    printf("\n");

    printf("Postorder traversal of the binary tree: ");
    postorder(root);
    printf("\n");

    printf("Display Binary tree structure:\n");
    displayTree(root, 0);

    // Searching for a node
    int searchData = 5;
    TreeNode* searchResult = search(root, searchData);
    if (searchResult != NULL) {
        printf("\nNode with data %d found in the binary tree.\n", searchData);
    } else {
        printf("\nNode with data %d not found in the binary tree.\n", searchData);
    }

    // Free the memory allocated for the tree
    freeTree(root);

    return 0;
}
