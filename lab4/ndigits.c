#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_A_LEN 101
#define MAX_EXPR_LEN 300


long long evaluate_expression(const char *expr) {
    long long stack[100];
    int top = -1;
    long long num = 0;
    char last_op = '+';

    for (int i = 0; expr[i]; i++) {
        if (isdigit(expr[i])) {
            num = num * 10 + (expr[i] - '0');
        }
        if (!isdigit(expr[i]) || expr[i + 1] == '\0') {
            if (expr[i + 1] == '\0' && isdigit(expr[i])) {
                i++;
            }
            if (last_op == '*') {
                stack[top] *= num;
            } else if (last_op == '/') {
                if (num == 0) return LLONG_MAX;
                stack[top] /= num;
            } else {
                stack[++top] = (last_op == '-') ? -num : num;
            }
            if (!isdigit(expr[i])) {
                last_op = expr[i];
                num = 0;
            }
        }
    }

    long long result = 0;
    for (int i = 0; i <= top; i++) {
        result += stack[i];
    }
    return result;
}


int generate_expressions(char *a, int pos, char *expr, int expr_pos, long long b, char *result_expr) {
    int len = strlen(a);
    if (pos == len) {
        expr[expr_pos] = '\0';
        if (evaluate_expression(expr) == b) {
            strcpy(result_expr, expr);
            return 1;
        }
        return 0;
    }

    int found = 0;
    expr[expr_pos] = a[pos];
    expr[expr_pos + 1] = '\0';
    found |= generate_expressions(a, pos + 1, expr, expr_pos + 1, b, result_expr);

    if (pos < len - 1) {
        const char operations[] = {'+', '-', '*', '/'};
        for (int i = 0; i < 4; i++) {
            expr[expr_pos + 1] = operations[i];
            found |= generate_expressions(a, pos + 1, expr, expr_pos + 2, b, result_expr);
        }
    }
    return found;
}


int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (!input || !output) {
        fprintf(stderr, "Error opening files\n");
        return 1;
    }

    char a[MAX_A_LEN];
    long long b;
    fscanf(input, "%s %lld", a, &b);
    fclose(input);

    char expr[MAX_EXPR_LEN], result_expr[MAX_EXPR_LEN] = "0";
    if (generate_expressions(a, 0, expr, 0, b, result_expr)) {
        fprintf(output, "%s\n", result_expr);
    } else {
        fprintf(output, "0\n");
    }
    fclose(output);
    return 0;
}
