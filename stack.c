#include<stdio.h>
#include<stdlib.h>

struct Stack {
    int *items;
    int top;
    int capacity;
};

void init(struct Stack* stack,int capacity){
    stack->capacity = capacity;
    stack->items = (int*)malloc(stack->capacity * sizeof(int));
    stack->top = -1;
}

void resizeStack(struct Stack* stack){
    stack->capacity *= 2;
    stack->items = (int*)realloc(stack->items,stack->capacity * sizeof(int));
}

int isFull(struct Stack* stack){
    return stack->top == stack->capacity-1;
}

int isEmpty(struct Stack* stack){
    return stack->top == -1;
}

void push(struct Stack* stack,int value){
    if (isFull(stack)){
        resizeStack(stack);
    }
    stack->items[++stack->top] = value;
    printf("pushed %d onto the stack\n",value);
}

int pop(struct Stack* stack){
    if (isEmpty(stack)){
        printf("Stack is empty.\n");
        return -1;
    }else {
        return stack->items[stack->top--];
    }
}

int peek(struct Stack* stack){
    if(isEmpty(stack)){
        printf("Stack is empty.\n");
        return -1;
    } else {
        return stack->items[stack->top];
    }
}

void display(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
    } else {
        printf("Stack elements: ");
        for (int i = stack->top; i >= 0; i--) {
            printf("%d ", stack->items[i]);
        }
        printf("\n");
    }
}

int main(){
    struct Stack Mstack;
    init(&Mstack,2);
    push(&Mstack,4);
    push(&Mstack,3);
    push(&Mstack,6);

    display(&Mstack);
    printf("Popped element is %d\n", pop(&Mstack));

    free(Mstack.items);  // Free the dynamically allocated memory
    return 0;
}