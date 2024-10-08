#include <stdio.h>
#include <stdlib.h>

// Use typedef to define a new type 'Node' for 'struct Node'
typedef struct Node {
    int data;
    struct Node* next;
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
    return newNode;
}

// Function to insert a new node at the beginning of the circular list
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {  // If the list is empty
        *head = newNode;
        newNode->next = newNode;  // Point to itself
    } else {
        Node* temp = *head;
        while (temp->next != *head) {  // Traverse to find the last node
            temp = temp->next;
        }
        temp->next = newNode;  // Link last node to new node
        newNode->next = *head;  // Point new node to head
        *head = newNode;  // Update head
    }
    printf("Inserted %d at the beginning\n", data);
}

// Function to insert a new node at the end of the circular list
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = newNode;  // Point to itself
        printf("Inserted %d at the end\n", data);
        return;
    }

    Node* temp = *head;
    while (temp->next != *head) {  // Traverse to find the last node
        temp = temp->next;
    }
    temp->next = newNode;  // Link last node to new node
    newNode->next = *head;  // Point new node to head
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
    temp->next = newNode;  // Link previous node to new node
    printf("Inserted %d at index %d\n", data, index);
}

// Function to delete a node from the beginning of the circular list
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
        Node* last = *head;
        while (last->next != *head) {  // Find the last node
            last = last->next;
        }
        last->next = temp->next;  // Link last node to the second node
        *head = temp->next;  // Update head
        printf("Deleted %d from the beginning\n", temp->data);
        free(temp);
    }
}

// Function to delete a node from the end of the circular list
void deleteAtEnd(Node** head) {
    if (*head == NULL) {
        printf("List is empty! Cannot delete.\n");
        return;
    }

    Node* temp = *head;
    if (temp->next == *head) {  // If there's only one node
        printf("Deleted %d from the end\n", temp->data);
        free(temp);
        *head = NULL;
        return;
    }

    Node* prev = NULL;
    while (temp->next != *head) {  // Traverse to find the last node
        prev = temp;
        temp = temp->next;
    }

    printf("Deleted %d from the end\n", temp->data);
    prev->next = *head;  // Link second last node to head
    free(temp);  // Free the memory of the deleted node
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
    Node* prev = NULL;

    for (int i = 0; i < index; i++) {
        prev = temp;
        temp = temp->next;
        if (temp == *head) {  // If we loop back to head
            printf("Index out of bounds!\n");
            return;
        }
    }

    printf("Deleted %d from index %d\n", temp->data, index);
    prev->next = temp->next;  // Unlink the node to be deleted
    free(temp);  // Free the memory of the deleted node
}

// Function to display the circular linked list
void displayList(Node* head) {
    if (head == NULL) {
        printf("The list is empty!\n");
        return;
    }

    printf("Circular Linked List: ");
    Node* temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}

// Function to search for an element in the circular linked list
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

// Main function to demonstrate the Circular Linked List
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
