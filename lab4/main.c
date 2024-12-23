#include "Header.h"

char* merge(char* exp) {
    int i, j = 0;
    char* result = (char*)malloc(strlen(exp) + 1);
    for (i = 0; exp[i] != '\0'; i++) {
        if (exp[i] != ' ') {
            result[j] = exp[i];
            j++;
        }
    }
    result[j] = '\0'; 
    return result;
}

long long calculate(char* expression) {
    long long result = 0;
    long long current_number = 0;
    char operator = '+';  
    long long temp_result = 0; 
    expression = merge(expression);

    for (long long i = 0; expression[i] != '\0'; i++) {
        if (isdigit(expression[i])) {
            current_number = current_number * 10 + (expression[i] - '0');
        }

        if (!isdigit(expression[i]) || expression[i + 1] == '\0') {
            if (operator == '*' || operator == '/') {
                if (operator == '*') {
                    temp_result *= current_number;
                }
                else if (operator == '/') {
                    if (current_number != 0 && temp_result % current_number == 0) {
                        temp_result /= current_number;
                    }
                    else {
                        return -1; 
                    }
                }
            }
            else {
                result += temp_result;
                if (operator == '+') {
                    temp_result = current_number;
                }
                else if (operator == '-') {
                    temp_result = -current_number;
                }
            }
            operator = expression[i];
            current_number = 0;
        }
    }
    result += temp_result; 
    return result;
}

char* insert_operator(char* expression, char op, int index_place) {
    int new_size = strlen(expression) + 1; 

    if (new_size + 1 > MAX_EXPRESSION) { 
        printf("Error, length new expression is too much\n");
        exit(0); 
    }
    for (int i = new_size; i > 2 * index_place + 1; i--) {
        expression[i] = expression[i - 1];
    }
    expression[2 * index_place + 1] = op;
    expression[new_size] = '\0'; 
    return expression;
}

int generate_expressions(char* A, int B, FILE* output) {
    
    int len = strlen(A);
    char operators[] = { '+', '-', '*', '/', ' ' };
    long long num_exp = pow(5, len);

    for (long long i = 0; i < num_exp; i++) {
        char expression[MAX_EXPRESSION] = "";
        long long change_op = i;
        strcat(expression, A);
        for (int j = 0; j < len - 1; j++) {
            int op_index = change_op % 5;
            change_op/= 5;
            insert_operator(expression, operators[op_index], j);
                
          if (calculate(expression) == B) {
            fprintf(output, "%s\n", merge(expression));
            return 0;
          }
        }
    }
    return -1;
}

bool check_A(char* A) {
    int len = strlen(A);
    if (len < 1) {
        return false;
    }
    for (long long i = 0; i < len; i++) {
        if (!isdigit(A[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    char A[MAX_DIGITS];
    int B;

    FILE* input_file = fopen("input.txt", "r");
    if (!input_file) {
        printf(stderr, "Ошибка: не удалось открыть файл input.txt\n");
        return 1;
    }
    fscanf(input_file, "%s %d", A, &B);
    if (!check_A(A)) {
        printf("A is not digital expression\n");
        return 1;
    }
    fclose(input_file);
  
    FILE* output_file = fopen("output.txt", "w");
    if (!output_file) {
        printf(stderr, "Ошибка: не удалось открыть файл output.txt\n");
        return 1;
    }
    if (generate_expressions(A, B, output_file)!=0){
        fprintf(output_file, "0\n");
    }
    fclose(output_file);
    return 0;
}                    
