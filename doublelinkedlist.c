#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    newNode->next = *head;
    *head = newNode;
    printf("Inserted %d at the beginning\n", data);
}

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

void deleteAtBeginning(Node** head) {
    if (*head == NULL) {
        printf("The list is empty, nothing to delete.\n");
        return;
    }
    
    Node* temp = *head;
    *head = temp->next;
    
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    
    printf("Deleted %d from the beginning\n", temp->data);
    free(temp);
}

void deleteAtEnd(Node** head) {
    if (*head == NULL) {
        printf("The list is empty, nothing to delete.\n");
        return;
    }

    Node* temp = *head;
    
    if (temp->next == NULL) {
        printf("Deleted %d from the end\n", temp->data);
        free(temp);
        *head = NULL;
        return;
    }
    
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    printf("Deleted %d from the end\n", temp->data);
    temp->prev->next = NULL;
    free(temp);
}

void displayListForward(Node* head) {
    if (head == NULL) {
        printf("The list is empty!\n");
        return;
    }
    
    printf("List in Forward Order: ");
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void displayListBackward(Node* head) {
    if (head == NULL) {
        printf("The list is empty!\n");
        return;
    }
    
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    printf("List in Backward Order: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;  // Initialize an empty list
    
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    displayListForward(head);
    
    insertAtBeginning(&head, 5);
    displayListForward(head);
    
    deleteAtBeginning(&head);
    displayListForward(head);
    
    deleteAtEnd(&head);
    displayListForward(head);
    
    displayListBackward(head);
    
    return 0;
}
