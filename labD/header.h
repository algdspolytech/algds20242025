#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

typedef struct {
    int* data;
    int top;
    int capacity;
} Stack;

int WriteOutput(char* expr) {
    FILE* output;

    output = fopen("output.txt", "w");
    if (output == NULL) {
        perror("Error openning file");
        return 1;
    }
    if (fprintf(output, "%s", expr) < 0) {
        fprintf(stderr, "Error writing\n");
        fclose(output);
        return 1;
    }
    fclose(output);
    return 0;
}

Stack* CreateStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

int IsEmpty(Stack* stack) { return stack->top == -1; }

void Push(Stack* stack, int value) {
    if (stack->top == stack->capacity - 1) {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    stack->data[++stack->top] = value;
}

double Pop(Stack* stack) {
    if (IsEmpty(stack)) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return stack->data[stack->top--];
}

char* InfixToPostfix(char* infix) {
    char* postfix = (char*)malloc(strlen(infix) * 2 + 1);
    Stack* opStack = CreateStack(strlen(infix));
    int postfixIndex = 0;
    for (int i = 0; infix[i] != '\0'; ++i) {
        if (isdigit(infix[i])) {
            postfix[postfixIndex++] = infix[i];
            while (isdigit(infix[i + 1])) {
                postfix[postfixIndex++] = infix[++i];
            }
            postfix[postfixIndex++] = ' ';
        }

        else if (strchr("+-*/", infix[i]) != NULL) {
            while (!IsEmpty(opStack) && (infix[i] == '+' || infix[i] == '-') &&
                (opStack->data[opStack->top] == '+' ||
                    opStack->data[opStack->top] == '-' ||
                    opStack->data[opStack->top] == '*' ||
                    opStack->data[opStack->top] == '/')) {
                postfix[postfixIndex++] = opStack->data[opStack->top];
                postfix[postfixIndex++] = ' ';
                Pop(opStack);
            }
            Push(opStack, infix[i]);
        }
        else {
            fprintf(stderr, "Invalid format");
            exit(1);
        }
    }
    while (!IsEmpty(opStack)) {
        postfix[postfixIndex++] = opStack->data[opStack->top];
        postfix[postfixIndex++] = ' ';
        Pop(opStack);
    }
    postfix[postfixIndex - 1] = '\0';
    free(opStack->data);
    free(opStack);
    return postfix;
}

int CalculateExpression(char* expression) {
    char* postfix = InfixToPostfix(expression);
    Stack* numStack = CreateStack(strlen(postfix));
    char* token = strtok((char*)postfix, " ");
    while (token != NULL) {
        if (isdigit(*token)) {
            Push(numStack, atof(token));
        }
        else {
            int operand2 = Pop(numStack);
            int operand1 = Pop(numStack);
            if (*token == '+')
                Push(numStack, operand1 + operand2);
            else if (*token == '-')
                Push(numStack, operand1 - operand2);
            else if (*token == '*')
                Push(numStack, operand1 * operand2);
            else if (*token == '/') {
                if (operand2 == 0 || operand1 % operand2 != 0) {
                    return 0;
                }
                Push(numStack, operand1 / operand2);
            }
        }
        token = strtok(NULL, " ");
    }
    int result = Pop(numStack);
    free(numStack->data);
    free(numStack);
    return result;
}

char* RemoveSpaces(char* expr) {
    int len = strlen(expr);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    char* ptr = result;
    for (int i = 0; i < len; i++) {
        if (expr[i] != ' ') {
            *ptr++ = expr[i];
        }
    }
    *ptr = '\0';
    return result;
}

int GenerateExpressions(char* A, int B) {
    int len = strlen(A);
    char operators[] = { '+', '-', '*', '/', ' ' };
    int numOperators = sizeof(operators) / sizeof(operators[0]);
    long long numExpressions = (long long)pow(numOperators, len);

    for (long long i = 0; i < numExpressions; i++) {
        char expression[1000] = "";
        long long temp = i;
        strcat(expression, A);
        for (int j = 0; j < len - 1; j++) {
            int operatorIndex = temp % numOperators;
            temp /= numOperators;
            char op;
            if (operatorIndex == 4) {

                char* ptr = expression;
                ptr += j + j + 1;
                memmove(ptr + 1, ptr, strlen(ptr) + 1);
                *ptr = ' ';
            }
            else {
                op = operators[operatorIndex];
                char* ptr = expression;
                ptr += j + j + 1;
                memmove(ptr + 1, ptr, strlen(ptr) + 1);
                *ptr = op;
            }
        }

        char* finalExpr = RemoveSpaces(expression);
        int result = CalculateExpression(finalExpr);
        if (result == B) {
            WriteOutput(finalExpr);
            return 1;
        }
    }
    return 0;
}