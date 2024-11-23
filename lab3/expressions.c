#include "expressions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

Stack* createStack(int capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int item) {
    stack->array[++stack->top] = item;
}

int pop(Stack *stack) {
    return stack->array[stack->top--];
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
    return 0;
}

int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                perror("Деление на ноль");
                exit(1);
            } else {
                return a / b;
            }
    }
    return 0;
}

int evaluate_expression(const char *expr) {
    Stack *values = createStack(100);
    Stack *ops = createStack(100);

    for (int i = 0; expr[i]; i++) {
        if (isspace(expr[i])) continue;

        if (isdigit(expr[i])) {
            int val = 0;
            while (i < strlen(expr) && isdigit(expr[i])) {
                val = val * 10 + (expr[i] - '0');
                i++;
            }
            push(values, val);
            i--;
        } else {
            while (!isEmpty(ops) && precedence(ops->array[ops->top]) >= precedence(expr[i])) {
                int val2 = pop(values);
                int val1 = pop(values);
                char op = pop(ops);
                push(values, applyOperation(val1, val2, op));
            }
            push(ops, expr[i]);
        }
    }

    while (!isEmpty(ops)) {
        int val2 = pop(values);
        int val1 = pop(values);
        char op = pop(ops);
        push(values, applyOperation(val1, val2, op));
    }

    return pop(values);
}

int generate_combinations(const char* A, int index, char* current_expr, int expr_length, long long B, char* result) {
    int len = strlen(A);

    if (index == len) {
        current_expr[expr_length] = '\0';
        long long result_value = evaluate_expression(current_expr);
        if (result_value == B) {
            strcpy(result, current_expr);
            return 1;
        }
        return 0;
    }

    current_expr[expr_length] = A[index];
    current_expr[expr_length + 1] = '\0';

    if (generate_combinations(A, index + 1, current_expr, expr_length + 1, B, result)) {
        return 1;
    }

    if (index < len - 1) {
        const char operators[] = "+-*/";
        for (int i = 0; i < 4; i++) {
            current_expr[expr_length + 1] = operators[i];
            if (generate_combinations(A, index + 1, current_expr, expr_length + 2, B, result)) {
                return 1;
            }
        }
    }
    return 0;
}

void solve_task(const char* input_file, const char* output_file) {
    FILE* input = fopen(input_file, "r");
    FILE* output = fopen(output_file, "w");

    if (!input || !output) {
        fprintf(stderr, "Ошибка открытия файлов.\n");
        exit(1);
    }

    char A[MAX_LENGTH];
    long long B;

    fscanf(input, "%s %lld", A, &B);
    fclose(input);

    char current_expr[MAX_LENGTH * 2];
    char result[MAX_LENGTH * 2];
    result[0] = '\0';

    if (generate_combinations(A, 0, current_expr, 0, B, result)) {
        fprintf(output, "%s\n", result);
    } else {
        fprintf(output, "0\n");
    }

    fclose(output);
}