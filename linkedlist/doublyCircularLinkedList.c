#include <stdio.h>
#include <stdlib.h>

// Use typedef to define a new type 'Node' for 'struct Node'
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;  // Pointer to the previous node
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // Allocate memory for a new node
    if (newNode == NULL) {  // Check if memory allocation failed
        printf("Memory allocation failed!\n");
        exit(1);  // Exit program if memory allocation fails
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a new node at the beginning of the doubly circular list
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {  // If the list is empty
        *head = newNode;
        newNode->next = newNode;  // Point to itself
        newNode->prev = newNode;  // Point to itself
    } else {
        Node* tail = (*head)->prev;  // Get the last node
        newNode->next = *head;  // New node's next is current head
        newNode->prev = tail;  // New node's prev is tail
        tail->next = newNode;  // Old tail's next is new node
        (*head)->prev = newNode;  // Current head's prev is new node
        *head = newNode;  // Update head
    }
    printf("Inserted %d at the beginning\n", data);
}

// Function to insert a new node at the end of the doubly circular list
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = newNode;  // Point to itself
        newNode->prev = newNode;  // Point to itself
        printf("Inserted %d at the end\n", data);
        return;
    }

    Node* tail = (*head)->prev;  // Get the last node
    tail->next = newNode;  // Link last node to new node
    newNode->next = *head;  // New node points to head
    newNode->prev = tail;  // New node's prev is tail
    (*head)->prev = newNode;  // Head's prev points to new node
    printf("Inserted %d at the end\n", data);
}

// Function to insert a new node at a specific index
void insertAtIndex(Node** head, int data, int index) {
    if (index < 0) {
        printf("Invalid index!\n");
        return;
    }

    Node* newNode = createNode(data);
    if (index == 0) {
        insertAtBeginning(head, data);
        return;
    }

    Node* temp = *head;
    for (int i = 0; i < index - 1; i++) {
        temp = temp->next;
        if (temp == *head) {  // If we loop back to head
            printf("Index out of bounds!\n");
            free(newNode);  // Free the allocated memory
            return;
        }
    }

    newNode->next = temp->next;  // Link new node to the next node
    newNode->prev = temp;  // Link new node's prev to temp
    temp->next->prev = newNode;  // Link next node's prev to new node
    temp->next = newNode;  // Link temp to new node
    printf("Inserted %d at index %d\n", data, index);
}

// Function to delete a node from the beginning of the doubly circular list
void deleteAtBeginning(Node** head) {
    if (*head == NULL) {
        printf("List is empty! Cannot delete.\n");
        return;
    }

    Node* temp = *head;
    if (temp->next == *head) {  // If there's only one node
        free(temp);
        *head = NULL;
    } else {
        Node* tail = (*head)->prev;  // Get the last node
        *head = temp->next;  // Update head
        tail->next = *head;  // Link last node to new head
        (*head)->prev = tail;  // New head's prev points to last node
        printf("Deleted %d from the beginning\n", temp->data);
        free(temp);
    }
}

// Function to delete a node from the end of the doubly circular list
void deleteAtEnd(Node** head) {
    if (*head == NULL) {
        printf("List is empty! Cannot delete.\n");
        return;
    }

    Node* tail = (*head)->prev;  // Get the last node
    if (tail == *head) {  // If there's only one node
        printf("Deleted %d from the end\n", tail->data);
        free(tail);
        *head = NULL;
        return;
    }

    Node* newTail = tail->prev;  // Get the second last node
    newTail->next = *head;  // Link second last node to head
    (*head)->prev = newTail;  // Head's prev points to new tail
    printf("Deleted %d from the end\n", tail->data);
    free(tail);  // Free the memory of the deleted node
}

// Function to delete a node at a specific index
void deleteAtIndex(Node** head, int index) {
    if (*head == NULL) {
        printf("List is empty! Cannot delete.\n");
        return;
    }

    if (index < 0) {
        printf("Invalid index!\n");
        return;
    }

    if (index == 0) {
        deleteAtBeginning(head);
        return;
    }

    Node* temp = *head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
        if (temp == *head) {  // If we loop back to head
            printf("Index out of bounds!\n");
            return;
        }
    }

    printf("Deleted %d from index %d\n", temp->data, index);
    temp->prev->next = temp->next;  // Unlink the node to be deleted
    temp->next->prev = temp->prev;  // Unlink the node to be deleted
    free(temp);  // Free the memory of the deleted node
}

// Function to display the doubly circular linked list
void displayList(Node* head) {
    if (head == NULL) {
        printf("The list is empty!\n");
        return;
    }

    printf("Doubly Circular Linked List: ");
    Node* temp = head;
    do {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}

// Function to search for an element in the doubly circular linked list
void searchElement(Node* head, int data) {
    if (head == NULL) {
        printf("List is empty! Cannot search.\n");
        return;
    }

    Node* temp = head;
    int index = 0;
    do {
        if (temp->data == data) {
            printf("Element %d found at index %d\n", data, index);
            return;
        }
        temp = temp->next;
        index++;
    } while (temp != head);
    
    printf("Element %d not found in the list.\n", data);
}

// Main function to demonstrate the Doubly Circular Linked List
int main() {
    Node* head = NULL;

    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    displayList(head);

    insertAtBeginning(&head, 5);
    displayList(head);

    insertAtIndex(&head, 15, 2);
    displayList(head);

    deleteAtBeginning(&head);
    displayList(head);

    deleteAtEnd(&head);
    displayList(head);

    deleteAtIndex(&head, 1);
    displayList(head);

    searchElement(head, 20);

    return 0;
}
