#include<stdio.h>
#include<stdlib.h>

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

// Function to insert a new node at the beginning of the list
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
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
    printf("Inserted %d at the end\n", data);
}

void insertAtIndex(Node** head, int data, int index) {
    if (index < 0) {
        printf("Invalid index!\n");
        return;
    }

    Node* newNode = createNode(data);

    if (index == 0) {
        newNode->next = *head;
        *head = newNode;
        printf("Inserted %d at index %d\n", data, index);
        return;
    }

    Node* temp = *head;
    for (int i = 0; i < index - 1; i++) {
        if (temp == NULL) {  // If index is out of bounds
            printf("Index out of bounds!\n");
            free(newNode);  // Free the allocated memory
            return;
        }
        temp = temp->next;
    }

    newNode->next = temp->next;
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

    if (temp->next == NULL) {  // If there is only one node in the list
        printf("Deleted %d from the end\n", temp->data);
        free(temp);
        *head = NULL;
        return;
    }

    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    printf("Deleted %d from the end\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
}

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
        *head = temp->next;
        printf("Deleted %d from index %d\n", temp->data, index);
        free(temp);
        return;
    }

    // Traverse to the node just before the one to be deleted
    for (int i = 0; temp != NULL && i < index - 1; i++) {
        temp = temp->next;
    }

    // If the index is out of bounds
    if (temp == NULL || temp->next == NULL) {
        printf("Index out of bounds!\n");
        return;
    }

    // Node temp->next is the node to be deleted
    Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;  // Unlink the node to be deleted
    printf("Deleted %d from index %d\n", nodeToDelete->data, index);

    free(nodeToDelete);  // Free the memory of the deleted node
}

void displayList(Node* head) {
    if (head == NULL) {
        printf("The list is empty!\n");
        return;
    }

    printf("Linked List: ");
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

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

