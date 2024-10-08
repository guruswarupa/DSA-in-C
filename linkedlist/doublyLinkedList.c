#include <stdio.h>
#include <stdlib.h>

// Define the structure for a doubly linked list node
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a new node at the beginning of the list
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
    printf("Inserted %d at the beginning\n", data);
}

// Function to insert a new node at the end of the list
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        printf("Inserted %d at the end\n", data);
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
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
    for (int i = 0; temp != NULL && i < index - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Index out of bounds!\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
    printf("Inserted %d at index %d\n", data, index);
}

// Function to delete a node from the beginning of the list
void deleteAtBeginning(Node** head) {
    if (*head == NULL) {
        printf("List is empty! Cannot delete.\n");
        return;
    }

    Node* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    printf("Deleted %d from the beginning\n", temp->data);
    free(temp);
}

// Function to delete a node from the end of the list
void deleteAtEnd(Node** head) {
    if (*head == NULL) {
        printf("List is empty! Cannot delete.\n");
        return;
    }

    Node* temp = *head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    if (temp->prev != NULL) {
        temp->prev->next = NULL;
    } else {
        *head = NULL;  // If there was only one node
    }

    printf("Deleted %d from the end\n", temp->data);
    free(temp);
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

    Node* temp = *head;

    // If the node to be deleted is the first node
    if (index == 0) {
        deleteAtBeginning(head);
        return;
    }

    for (int i = 0; temp != NULL && i < index; i++) {
        temp = temp->next;
    }

    // If the index is out of bounds
    if (temp == NULL) {
        printf("Index out of bounds!\n");
        return;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    printf("Deleted %d from index %d\n", temp->data, index);
    free(temp);
}

// Function to display the doubly linked list
void displayList(Node* head) {
    if (head == NULL) {
        printf("The list is empty!\n");
        return;
    }

    printf("Doubly Linked List: ");
    Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to search for an element in the list
void searchElement(Node* head, int data) {
    Node* temp = head;
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

// Main function to test the doubly linked list operations
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
