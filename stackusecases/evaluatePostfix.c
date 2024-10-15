#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>  // For isdigit()

// Stack structure for integer type
typedef struct {
    int *items;
    int top;
    int capacity;
} Stack;

void init(Stack* stack, int capacity) {
    stack->capacity = capacity;
    stack->items = (int*)malloc(stack->capacity * sizeof(int));
    stack->top = -1;
}

void resizeStack(Stack* stack) {
    stack->capacity *= 2;
    stack->items = (int*)realloc(stack->items, stack->capacity * sizeof(int));
}

int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int value) {
    if (isFull(stack)) {
        resizeStack(stack);
    }
    stack->items[++stack->top] = value;
}

int pop(Stack* stack) {
    return isEmpty(stack) ? -1 : stack->items[stack->top--];
}

int peek(Stack* stack) {
    return isEmpty(stack) ? -1 : stack->items[stack->top];
}

// Function to evaluate the postfix expression
int evaluatePostfix(char* postfix) {
    Stack stack;
    init(&stack, 10);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char current = postfix[i];

        // If the current character is an operand, push it to the stack
        if (isdigit(current)) {
            push(&stack, current - '0');  // Convert character to integer
        }
        // If the current character is an operator, pop two operands and perform the operation
        else if (current == '+' || current == '-' || current == '*' || current == '/') {
            int operand2 = pop(&stack);  // Second operand
            int operand1 = pop(&stack);  // First operand

            switch (current) {
                case '+': push(&stack, operand1 + operand2); break;
                case '-': push(&stack, operand1 - operand2); break;
                case '*': push(&stack, operand1 * operand2); break;
                case '/': push(&stack, operand1 / operand2); break;
            }
        }
    }

    // The result will be the last item on the stack
    int result = pop(&stack);
    free(stack.items);  // Free the memory allocated to the stack
    return result;
}

int main() {
    char postfix[100];

    printf("Enter a postfix expression: ");
    scanf("%s", postfix);

    int result = evaluatePostfix(postfix);
    printf("Result of postfix evaluation: %d\n", result);

    return 0;
}
