#include<stdio.h>
#include<stdlib.h>

struct Queue {
    int *items;
    int front;
    int rear;
    int capacity;
};

void init(struct Queue* queue,int capacity){
    queue->capacity = capacity;
    queue->items = (int*)malloc(queue->capacity * sizeof(int));
    queue->front = -1;
    queue->rear = -1;
}

void resizeQueue(struct Queue* queue){
    queue->capacity*=2;
    queue->items = (int*)realloc(queue->items,queue->capacity * sizeof(int));
}

int isFull(struct Queue* queue){
    return queue->rear == queue->capacity - 1;
}

int isEmpty(struct Queue* queue){
    return queue->front == queue->rear-1;
}

void enqueue(struct Queue* queue,int value){
    if(isFull(queue)){
        resizeQueue(queue);
    }
    if (queue->front == -1)
        queue->front =0;
    queue->items[++queue->rear] = value;
    printf("Enqueued %d \n",value);
}

int dequeue(struct Queue* queue){
    if(isEmpty(queue)){
        printf("Queue is empty");
        return -1;
    } else {
        int dequeuedItem = queue->items[queue->front++];
        if (queue->front > queue->rear){
            queue->front = -1;
            queue->rear = -1;
        }
        return dequeuedItem;
    }
}

void display(struct Queue* queue){
    if (isEmpty(queue)){
        printf("Queue is Empty.");
    } else {
        printf("Queue elements: ");
        for(int i=queue->front; i<=queue->rear; i++){
            printf("%d ", queue->items[i]);
        }
        printf("\n");
    }
}

int main(){
    struct Queue myQueue;  // Declare a queue variable
    init(&myQueue, 2);  // Initialize the queue with initial capacity 2

    // Test the queue operations
    enqueue(&myQueue, 10);
    enqueue(&myQueue, 20);
    enqueue(&myQueue, 30);  // This will trigger a resize
    enqueue(&myQueue, 40);

    display(&myQueue);  // Display the queue

    printf("Dequeued element is %d\n", dequeue(&myQueue));
    display(&myQueue);  // Display after dequeuing

    free(myQueue.items);  // Free the dynamically allocated memory
    return 0;
}