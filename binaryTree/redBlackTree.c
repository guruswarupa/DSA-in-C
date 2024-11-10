#include <stdio.h>
#include <stdlib.h>

// Enum for node color
typedef enum { RED, BLACK } Color;

// Structure for a tree node
typedef struct RBTreeNode {
    int data;
    struct RBTreeNode* left;
    struct RBTreeNode* right;
    struct RBTreeNode* parent;
    Color color; // Color of the node
} RBTreeNode;

// Function to create a new node
RBTreeNode* createNode(int data) {
    RBTreeNode* newNode = (RBTreeNode*)malloc(sizeof(RBTreeNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = newNode->parent = NULL;
    newNode->color = RED; // New node is initially red
    return newNode;
}

// Function to perform a left rotate
void leftRotate(RBTreeNode** root, RBTreeNode* x) {
    RBTreeNode* y = x->right;
    x->right = y->left;

    if (y->left != NULL) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL) {
        *root = y; // y becomes the new root
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

// Function to perform a right rotate
void rightRotate(RBTreeNode** root, RBTreeNode* y) {
    RBTreeNode* x = y->left;
    y->left = x->right;

    if (x->right != NULL) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == NULL) {
        *root = x; // x becomes the new root
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

// Function to fix the Red-Black Tree properties after insertion
void fixInsert(RBTreeNode** root, RBTreeNode* node) {
    while (node != *root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            RBTreeNode* uncle = node->parent->parent->right;

            // Case 1: Uncle is red
            if (uncle != NULL && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                // Case 2: node is the right child
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(root, node);
                }

                // Case 3: node is the left child
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(root, node->parent->parent);
            }
        } else {
            RBTreeNode* uncle = node->parent->parent->left;

            // Case 1: Uncle is red
            if (uncle != NULL && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                // Case 2: node is the left child
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(root, node);
                }

                // Case 3: node is the right child
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(root, node->parent->parent);
            }
        }
    }

    (*root)->color = BLACK;
}

// Function to insert a node into the Red-Black Tree
RBTreeNode* insert(RBTreeNode* root, int data) {
    RBTreeNode* newNode = createNode(data);
    RBTreeNode* parent = NULL;
    RBTreeNode* current = root;

    // Perform standard BST insert
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;
    if (parent == NULL) {
        root = newNode; // The tree was empty
    } else if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    // Fix Red-Black Tree violations
    fixInsert(&root, newNode);
    return root;
}

// Function to search for a node in the Red-Black Tree
RBTreeNode* search(RBTreeNode* root, int data) {
    while (root != NULL && root->data != data) {
        if (data < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

// Inorder traversal
void inorder(RBTreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder traversal
void preorder(RBTreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder traversal
void postorder(RBTreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Function to display the tree graphically (similar to AVL tree)
void displayTree(RBTreeNode* root, int space) {
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
    printf("%d (%s)", root->data, (root->color == RED) ? "R" : "B");

    // Process left child
    displayTree(root->left, space);
}

// Function to free memory of the tree
void freeTree(RBTreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Main function
int main() {
    RBTreeNode* root = NULL;

    // Insert nodes into the Red-Black tree
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 10);
    root = insert(root, 25);
    root = insert(root, 35);
    root = insert(root, 50);
    root = insert(root, 90);
    root = insert(root, 150);
    root = insert(root, 120);
    root = insert(root, 160);
    root = insert(root, 190);
    root = insert(root, 155);
    root = insert(root, 130);
    root = insert(root, 200);

    printf("Inorder traversal of the Red-Black tree: ");
    inorder(root);
    printf("\n");

    printf("Preorder traversal of the Red-Black tree: ");
    preorder(root);
    printf("\n");

    printf("Postorder traversal of the Red-Black tree: ");
    postorder(root);
    printf("\n");

    printf("Display Red-Black tree structure:\n");
    displayTree(root, 0);

    // Searching for a node
    int searchData = 25;
    RBTreeNode* searchResult = search(root, searchData);
    if (searchResult != NULL) {
        printf("\nNode with data %d found in the Red-Black tree.\n", searchData);
    } else {
        printf("\nNode with data %d not found in the Red-Black tree.\n", searchData);
    }

    // Free the memory allocated for the tree
    freeTree(root);
    
    return 0;
}
