#ifndef EXPRESSION_SOLVER_H
#define EXPRESSION_SOLVER_H

#define MAX_LENGTH 110

typedef struct {
    int top;
    int capacity;
    int *array;
} Stack;

// Прототипы функций
Stack* createStack(int capacity);
int isEmpty(Stack *stack);
void push(Stack *stack, int item);
int pop(Stack *stack);
int precedence(char op);
int applyOperation(int a, int b, char op);
int evaluate_expression(const char *expr);
int generate_combinations(const char* A, int index, char* current_expr, int expr_length, long long B, char* result);
void solve_task(const char* input_file, const char* output_file);

#endif // EXPRESSION_SOLVER_H