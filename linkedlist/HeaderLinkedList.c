#include <stdio.h>
#include <stdlib.h>

// Node structure with a pointer to the next node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // Allocate memory for a new node
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);  // Exit if memory allocation fails
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a header node
Node* createHeader() {
    Node* header = createNode(0);  // Create the header node with 0 as dummy data
    return header;
}

// Function to insert a node at the beginning of the list
void insertAtBeginning(Node* header, int data) {
    Node* newNode = createNode(data);  // Create a new node
    newNode->next = header->next;  // New node points to the current first node
    header->next = newNode;  // Header points to the new node
    printf("Inserted %d at the beginning\n", data);
}

// Function to insert a node at the end of the list
void insertAtEnd(Node* header, int data) {
    Node* newNode = createNode(data);  // Create a new node
    Node* temp = header;  // Temporary pointer to traverse the list
    while (temp->next != NULL) {
        temp = temp->next;  // Move to the last node
    }
    temp->next = newNode;  // The last node points to the new node
    printf("Inserted %d at the end\n", data);
}

// Function to insert a node at a specific index
void insertAtIndex(Node* header, int data, int index) {
    if (index < 0) {
        printf("Invalid index!\n");
        return;
    }

    Node* newNode = createNode(data);
    Node* temp = header;

    for (int i = 0; i < index; i++) {
        if (temp->next == NULL && i != index - 1) {
            printf("Index out of bounds!\n");
            free(newNode);
            return;
        }
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    printf("Inserted %d at index %d\n", data, index);
}

// Function to delete a node from the beginning of the list
void deleteAtBeginning(Node* header) {
    if (header->next == NULL) {
        printf("List is empty! Cannot delete.\n");
        return;
    }

    Node* temp = header->next;  // Get the node to be deleted
    header->next = temp->next;  // Header points to the second node
    printf("Deleted %d from the beginning\n", temp->data);
    free(temp);  // Free the memory of the deleted node
}

// Function to delete a node from the end of the list
void deleteAtEnd(Node* header) {
    if (header->next == NULL) {
        printf("List is empty! Cannot delete.\n");
        return;
    }

    Node* temp = header;
    // Traverse until we find the second last node
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    Node* lastNode = temp->next;  // Last node to be deleted
    printf("Deleted %d from the end\n", lastNode->data);
    free(lastNode);  // Free memory of the last node
    temp->next = NULL;  // Now the second last node is the last node
}

// Function to delete a node at a specific index
void deleteAtIndex(Node* header, int index) {
    if (index < 0 || header->next == NULL) {
        printf("Invalid index or list is empty!\n");
        return;
    }

    Node* temp = header;

    for (int i = 0; i < index; i++) {
        if (temp->next == NULL) {
            printf("Index out of bounds!\n");
            return;
        }
        temp = temp->next;
    }

    Node* nodeToDelete = temp->next;
    if (nodeToDelete == NULL) {
        printf("Index out of bounds!\n");
        return;
    }

    temp->next = nodeToDelete->next;
    printf("Deleted %d from index %d\n", nodeToDelete->data, index);
    free(nodeToDelete);
}

// Function to search for an element in the list
void searchElement(Node* header, int data) {
    Node* temp = header->next;  // Start from the first actual node
    int index = 0;

    while (temp != NULL) {
        if (temp->data == data) {
            printf("Element %d found at index %d\n", data, index);
            return;
        }
        temp = temp->next;
        index++;
    }

    printf("Element %d not found in the list.\n", data);
}

// Function to display the length of the list
int getLength(Node* header) {
    int length = 0;
    Node* temp = header->next;  // Start from the first actual node
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}

// Function to display the linked list
void displayList(Node* header) {
    if (header->next == NULL) {
        printf("The list is empty!\n");
        return;
    }

    Node* temp = header->next;  // Start from the first actual node
    printf("Header Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);  // Print each node's data
        temp = temp->next;  // Move to the next node
    }
    printf("NULL\n");  // End of the list
}

// Main function to demonstrate the operations on the Header Linked List
int main() {
    Node* header = createHeader();  // Create the header linked list

    insertAtEnd(header, 10);  // Insert 10 at the end
    insertAtEnd(header, 20);  // Insert 20 at the end
    insertAtEnd(header, 30);  // Insert 30 at the end
    displayList(header);      // Display the list

    insertAtBeginning(header, 5);  // Insert 5 at the beginning
    displayList(header);           // Display the list

    insertAtIndex(header, 25, 2);  // Insert 25 at index 2
    displayList(header);           // Display the list

    deleteAtBeginning(header);  // Delete from the beginning
    displayList(header);        // Display the list

    deleteAtEnd(header);  // Delete from the end
    displayList(header);  // Display the list

    deleteAtIndex(header, 1);  // Delete element at index 1
    displayList(header);       // Display the list

    searchElement(header, 20);  // Search for 20 in the list

    printf("Length of the list: %d\n", getLength(header));  // Get the length of the list

    return 0;
}
