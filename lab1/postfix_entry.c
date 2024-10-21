#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <C:/Users/vicro/Desktop/Algosy_lab2/postfix_entry/postfix_entry/postfix_entry.h>



void initStack(Stack* stack) {
    stack->top = -1;
}


int isEmpty(Stack* stack) {
    return stack->top == -1;
}


int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}


void push(Stack* stack, char value) {
    if (!isFull(stack)) {
        stack->data[++(stack->top)] = value;
    }
    else {
        printf("Stack overflow\n");
        exit(1);
    }
}


char pop(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->data[(stack->top)--];
    }
    else {
        printf("Stack underflow\n");
        exit(1);
    }
}


char peek(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top];
    }
    else {
        return '\0';
    }
}


int precedence(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return -1;
}


void infixToPostfix(char* infix, char* postfix) {
    Stack stack;
    initStack(&stack);
    int i, j;
    char c;

    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        c = infix[i];

        if (isalnum(c)) {
            postfix[j++] = c;
        }
        else if (c == '(') {
            push(&stack, c);
        }
        else if (c == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            if (!isEmpty(&stack) && peek(&stack) != '(') {
                printf("Invalid expression\n");
                exit(1);
            }
            else {
                pop(&stack);
            }
        }
        else {
            while (!isEmpty(&stack) && precedence(c) <= precedence(peek(&stack))) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, c);
        }
    }

    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
}


int readFromFile(const char* filename, char* buffer, int bufferSize) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening input file\n");
        return 0;
    }

    if (fgets(buffer, bufferSize, file) == NULL) {
        printf("Error reading from file\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}


int writeToFile(const char* filename, const char* buffer) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening output file\n");
        return 0;
    }

    fprintf(file, "%s", buffer);
    fclose(file);
    return 1;
}


/*int main() {
    char infix[100];
    if (!readFromFile("input.txt", infix, sizeof(infix))) {
        return 1;
    }

    char postfix[100];
    infixToPostfix(infix, postfix);

    if (!writeToFile("output.txt", postfix)) {
        return 1;
    }

    printf("Postfix expression written to output.txt\n");

    return 0;
}*/