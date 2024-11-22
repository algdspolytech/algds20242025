#include "Header.h"

long long eval_expression(const char* expr) {
    long long result = 0, current = 0;
    char operation = '+';
    long long stack[MAX_LEN] = { 0 };
    int top = 0;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] >= '0' && expr[i] <= '9') {
            current = current * 10 + (expr[i] - '0');
        }
        else {
            switch (operation) {
            case '+': stack[top++] = current; break;
            case '-': stack[top++] = -current; break;
            case '*': stack[top - 1] *= current; break;
            case '/':
                if (current == 0) return LLONG_MAX;
                stack[top - 1] /= current; break;
            }
            operation = expr[i];
            current = 0;
        }
    }

    switch (operation) {
    case '+': stack[top++] = current; break;
    case '-': stack[top++] = -current; break;
    case '*': stack[top - 1] *= current; break;
    case '/':
        if (current == 0) return LLONG_MAX;
        stack[top - 1] /= current; break;
    }

    for (int i = 0; i < top; i++) {
        result += stack[i];
    }

    return result;
}

bool solve(const char* A, int B, int index, char* expr, int expr_index) {
    if (A[index] == '\0') {
        expr[expr_index] = '\0';
        return eval_expression(expr) == B;
    }

    expr[expr_index] = A[index];
    expr[expr_index + 1] = '\0';

    if (solve(A, B, index + 1, expr, expr_index + 1)) {
        return true;
    }

    char operators[] = "+-*/";
    for (int i = 0; operators[i] != '\0'; ++i) {
        expr[expr_index + 1] = operators[i];
        if (solve(A, B, index + 1, expr, expr_index + 2)) {
            return true;
        }
    }

    return false;
}

bool find_expression(const char* A, int B, char* result) {
    char expr[2 * MAX_LEN] = { 0 };
    if (solve(A, B, 0, expr, 0)) {
        strcpy(result, expr);
        return true;
    }
    return false;
}