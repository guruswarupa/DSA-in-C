#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>  // For isdigit() and isalpha()

// Stack structure for char type
typedef struct {
    char *items;
    int top;
    int capacity;
} Stack;

void init(Stack* stack, int capacity) {
    stack->capacity = capacity;
    stack->items = (char*)malloc(stack->capacity * sizeof(char));
    stack->top = -1;
}

void resizeStack(Stack* stack) {
    stack->capacity *= 2;
    stack->items = (char*)realloc(stack->items, stack->capacity * sizeof(char));
}

int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, char value) {
    if (isFull(stack)) {
        resizeStack(stack);
    }
    stack->items[++stack->top] = value;
}

char pop(Stack* stack) {
    return isEmpty(stack) ? -1 : stack->items[stack->top--];
}

char peek(Stack* stack) {
    return isEmpty(stack) ? -1 : stack->items[stack->top];
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    if (op == '^') {
        return 3;
    }
    return 0;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void infixToPostfix(char* infix) {
    Stack operatorStack;
    init(&operatorStack, 10);

    char postfix[100];
    int k = 0;  // Index for the postfix expression

    for (int i = 0; infix[i] != '\0'; i++) {
        char current = infix[i];

        // If the character is an operand (either letter or digit)
        if (isalnum(current)) {
            postfix[k++] = current;
        }
        // If the character is an opening parenthesis
        else if (current == '(') {
            push(&operatorStack, current);
        }
        // If the character is a closing parenthesis
        else if (current == ')') {
            while (!isEmpty(&operatorStack) && peek(&operatorStack) != '(') {
                postfix[k++] = pop(&operatorStack);
            }
            pop(&operatorStack);  // Pop the '('
        }
        // If the character is an operator
        else if (isOperator(current)) {
            while (!isEmpty(&operatorStack) && precedence(current) <= precedence(peek(&operatorStack))) {
                postfix[k++] = pop(&operatorStack);
            }
            push(&operatorStack, current);
        }
    }

    // Pop all remaining operators from the stack
    while (!isEmpty(&operatorStack)) {
        postfix[k++] = pop(&operatorStack);
    }

    postfix[k] = '\0';  // Null-terminate the postfix expression

    printf("Postfix Expression: %s\n", postfix);

    free(operatorStack.items);  // Free memory allocated to the stack
}

int main() {
    char infix[100];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix);

    return 0;
}
