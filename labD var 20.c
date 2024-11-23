#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define _CRTDBG_MAP_ALLOC

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>

int* result;
int result_size = 0;

int find_subset(int* elements, int n, unsigned long long target, int start) {
    if (target == 0) {
        return 1; 
    }
    if (target < 0) {
        return 0; 
    }

    for (int i = start; i < n; i++) {
        result[result_size++] = elements[i]; 

        if (find_subset(elements, n, target - elements[i], i + 1)) {
            return 1; 
        }

        result_size--; 
    }

    return 0; 
}

void solve_problem(const char* input_file, const char* output_file) {
    FILE* in_file = fopen(input_file, "r");
    FILE* out_file = fopen(output_file, "w");

    if (!in_file || !out_file) {
        perror("Ошибка открытия файла");
        return;
    }

    unsigned long long target_sum;
    fscanf(in_file, "%llu", &target_sum);

    int n;
    fscanf(in_file, "%d", &n);

    if (n <= 0 || n >= 1000) {
        fprintf(out_file, "0\n");
        fclose(in_file);
        fclose(out_file);
        return;
    }

    int* elements = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(in_file, "%d", &elements[i]);
    }

    fclose(in_file);

    result = malloc(n * sizeof(int)); 

    if (find_subset(elements, n, target_sum, 0)) {
        for (int i = 0; i < result_size; i++) {
            fprintf(out_file, "%d ", result[i]);
        }
    }
    else {
        fprintf(out_file, "0\n"); 
    }

    fclose(out_file);
    free(elements);
    free(result);
}

int main() {
    solve_problem("input.txt", "output.txt");
    return 0;
}
