#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "knapsack.h"

void verify_solution(int U, int B, int K, const int* weights, const int* values, int* solution, int solution_count) {
    int total_weight = 0;
    int total_value = 0;
    for (int i = 0; i < solution_count; i++) {
        int item = solution[i];
        total_weight += weights[item];
        total_value += values[item];
    }
    assert(total_weight <= B);
    assert(total_value >= K);
}

void test_basic() {
    int U = 3;
    int B = 4;
    int K = 6;
    int weights[] = { 1, 2, 3 };
    int values[] = { 2, 3, 4 };
    int solution[3];
    int solution_count;
    int found = knapsack_memoization(U, B, K, weights, values, solution, &solution_count);
    assert(found == 1);
    verify_solution(U, B, K, weights, values, solution, solution_count);
}

void test_no_solution_weight() {
    int U = 2;
    int B = 3;
    int K = 1;
    int weights[] = { 4, 5 };
    int values[] = { 2, 3 };
    int solution[2];
    int solution_count;
    int found = knapsack_memoization(U, B, K, weights, values, solution, &solution_count);
    assert(found == 0);
}

void test_no_solution_value() {
    int U = 2;
    int B = 5;
    int K = 10;
    int weights[] = { 3, 2 };
    int values[] = { 4, 5 };
    int solution[2];
    int solution_count;
    int found = knapsack_memoization(U, B, K, weights, values, solution, &solution_count);
    assert(found == 0);
}

void test_exact_match() {
    int U = 1;
    int B = 5;
    int K = 5;
    int weights[] = { 5 };
    int values[] = { 5 };
    int solution[1];
    int solution_count;
    int found = knapsack_memoization(U, B, K, weights, values, solution, &solution_count);
    assert(found == 1);
    assert(solution_count == 1);
    verify_solution(U, B, K, weights, values, solution, solution_count);
}

void test_all_items() {
    int U = 3;
    int B = 9;
    int K = 12;
    int weights[] = { 2, 3, 4 };
    int values[] = { 3, 4, 5 };
    int solution[3];
    int solution_count;
    int found = knapsack_memoization(U, B, K, weights, values, solution, &solution_count);
    assert(found == 1);
    assert(solution_count == 3);
    verify_solution(U, B, K, weights, values, solution, solution_count);
}

void test_zero_capacity() {
    int U = 2;
    int B = 0;
    int K = 0;
    int weights[] = { 0, 0 };
    int values[] = { 5, 3 };
    int solution[2];
    int solution_count;
    int found = knapsack_memoization(U, B, K, weights, values, solution, &solution_count);
    assert(found == 1);
    verify_solution(U, B, K, weights, values, solution, solution_count);
}

void test_k_zero() {
    int U = 2;
    int B = 3;
    int K = 0;
    int weights[] = { 2, 1 };
    int values[] = { 5, 4 };
    int solution[2];
    int solution_count;
    int found = knapsack_memoization(U, B, K, weights, values, solution, &solution_count);
    assert(found == 1);
    verify_solution(U, B, K, weights, values, solution, solution_count);
}

void test_single_item_fits() {
    int U = 1;
    int B = 5;
    int K = 5;
    int weights[] = { 5 };
    int values[] = { 5 };
    int solution[1];
    int solution_count;
    int found = knapsack_memoization(U, B, K, weights, values, solution, &solution_count);
    assert(found == 1);
    assert(solution_count == 1);
    verify_solution(U, B, K, weights, values, solution, solution_count);
}

void test_single_item_no_fit() {
    int U = 1;
    int B = 4;
    int K = 5;
    int weights[] = { 5 };
    int values[] = { 10 };
    int solution[1];
    int solution_count;
    int found = knapsack_memoization(U, B, K, weights, values, solution, &solution_count);
    assert(found == 0);
}

void test_duplicate_items() {
    int U = 3;
    int B = 6;
    int K = 6;
    int weights[] = { 2, 2, 2 };
    int values[] = { 2, 2, 2 };
    int solution[3];
    int solution_count;
    int found = knapsack_memoization(U, B, K, weights, values, solution, &solution_count);
    assert(found == 1);
    verify_solution(U, B, K, weights, values, solution, solution_count);
    assert(solution_count == 3);
}

void test_zero_weight_items() {
    int U = 2;
    int B = 5;
    int K = 10;
    int weights[] = { 0, 0 };
    int values[] = { 6, 5 };
    int solution[2];
    int solution_count;
    int found = knapsack_memoization(U, B, K, weights, values, solution, &solution_count);
    assert(found == 1);
    verify_solution(U, B, K, weights, values, solution, solution_count);
    assert(solution_count == 2);
}

void test_minimal_weight_subset() {
    int U = 3;
    int B = 5;
    int K = 10;
    int weights[] = { 3, 2, 2 };
    int values[] = { 5, 5, 5 };
    int solution[3];
    int solution_count;
    int found = knapsack_memoization(U, B, K, weights, values, solution, &solution_count);
    assert(found == 1);
    verify_solution(U, B, K, weights, values, solution, solution_count);
    int total_weight = 0;
    for (int i = 0; i < solution_count; i++) {
        total_weight += weights[solution[i]];
    }
    assert(total_weight == 4);
}

void test_read_input() {
    const char* filename = "input.txt";
    FILE* file = fopen(filename, "w");
    fprintf(file, "3 10 5\n");
    fprintf(file, "1 2 3\n");
    fprintf(file, "4 5 6\n");
    fclose(file);

    int U, B, K;
    int* weights, * values;
    read_input(filename, &U, &B, &K, &weights, &values);

    assert(U == 3);
    assert(B == 10);
    assert(K == 5);
    assert(weights[0] == 1);
    assert(weights[1] == 2);
    assert(weights[2] == 3);
    assert(values[0] == 4);
    assert(values[1] == 5);
    assert(values[2] == 6);

    free(weights);
    free(values);
}


int main() {

    test_basic();
    test_no_solution_weight();
    test_no_solution_value();
    test_exact_match();
    test_all_items();
    test_zero_capacity();
    test_k_zero();
    test_single_item_fits();
    test_single_item_no_fit();
    test_duplicate_items();
    test_zero_weight_items();
    test_minimal_weight_subset();
    test_read_input();

    printf("All tests passed!\n");
    return 0;
}