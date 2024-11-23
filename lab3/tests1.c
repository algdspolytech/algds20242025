//
//  tests.c
//  Lab_D
//
//  Created by Фёдор Филь on 21.11.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "tests.h"
#include "main.h"

void test_readInput_simple_case_no1(void) {
    const char *test_input =
        "3 5\n"
        "1 -1 -2\n"
        "1 2\n"
        "2 3\n"
        "0";

    FILE *temp_in = fmemopen((char *)test_input, strlen(test_input), "r");
    int T, K;
    int *Z;
    ArrayList *graph;

    readInput(temp_in, &T, &K, &Z, &graph);

    assert(T == 3);
    assert(K == 5);
    assert(Z[0] == 1);
    assert(Z[1] == -1);
    assert(Z[2] == -2);
    assert(graph[1].used == 1);
    assert(graph[1].array[0] == 2);
    assert(graph[2].used == 1);
    assert(graph[2].array[0] == 3);
    assert(graph[3].used == 0);

    free(Z);
    freeGraph(graph, T);
    fclose(temp_in);
}

void test_readInput_with_negative_z_values_no2(void) {
    const char *test_input =
        "4 2\n"
        "-1 -2 -3 -4\n"
        "1 2\n"
        "2 3\n"
        "3 4\n"
        "0";

    FILE *temp_in = fmemopen((char *)test_input, strlen(test_input), "r");
    int T, K;
    int *Z;
    ArrayList *graph;

    readInput(temp_in, &T, &K, &Z, &graph);

    assert(T == 4);
    assert(K == 2);
    assert(Z[0] == -1);
    assert(Z[1] == -2);
    assert(Z[2] == -3);
    assert(Z[3] == -4);
    assert(graph[1].used == 1);
    assert(graph[1].array[0] == 2);
    assert(graph[2].used == 1);
    assert(graph[2].array[0] == 3);
    assert(graph[3].used == 1);
    assert(graph[3].array[0] == 4);
    assert(graph[4].used == 0);

    free(Z);
    freeGraph(graph, T);
    fclose(temp_in);
}

void test_readInput_invalid_format_no3(void) {
    const char *test_input =
        "2 10\n"
        "1 2\n"
        "1 2\n"
        "2 3\n"
        "3 4\n"
        "0";

    FILE *temp_in = fmemopen((char *)test_input, strlen(test_input), "r");
    int T, K;
    int *Z;
    ArrayList *graph;

    readInput(temp_in, &T, &K, &Z, &graph);

    assert(T == 2);
    assert(K == 10);
    assert(Z[0] == 1);
    assert(Z[1] == 2);
    assert(graph[1].used == 1);
    assert(graph[1].array[0] == 2);
    assert(graph[2].used == 0);

    free(Z);
    freeGraph(graph, T);
    fclose(temp_in);
}

void test_topologicalSort_no_cycles_no4(void) {
    const int MAX_T = 5;
    ArrayList graph[MAX_T + 1];

    for (int i = 1; i <= 5; ++i) {
        initArrayList(&graph[i], 10);
    }

    insertArrayList(&graph[1], 2);
    insertArrayList(&graph[2], 3);
    insertArrayList(&graph[3], 4);
    insertArrayList(&graph[3], 5);

    ArrayList *result = topologicalSort(graph, 5);

    assert(result != NULL);
    assert(result->used == 5);
    assert(result->array[0] == 1);
    assert(result->array[1] == 2);
    assert(result->array[2] == 3);
    assert(result->array[3] == 4);
    assert(result->array[4] == 5);

    freeArrayList(result);
}

void test_topologicalSort_cycle_detected_no5(void) {
    const int MAX_T = 3;
    ArrayList graph[MAX_T + 1];

    for (int i = 1; i <= 3; ++i) {
        initArrayList(&graph[i], 10);
    }

    insertArrayList(&graph[1], 2);
    insertArrayList(&graph[2], 3);
    insertArrayList(&graph[3], 1);

    ArrayList *result = topologicalSort(graph, 3);

    assert(result == NULL);
}

void test_topologicalSort_empty_graph_no6(void) {
    const int MAX_T = 0;
    ArrayList graph[MAX_T + 1];

    for (int i = 1; i <= 0; ++i) {
        initArrayList(&graph[i], 10);
    }

    ArrayList *result = topologicalSort(graph, 0);

    assert(result == NULL);
}

void test_topologicalSort_complex_graph_no7(void) {
    const int MAX_T = 7;
    ArrayList graph[MAX_T + 1];

    for (int i = 1; i <= 7; ++i) {
        initArrayList(&graph[i], 10);
    }

    insertArrayList(&graph[1], 2);
    insertArrayList(&graph[1], 3);
    insertArrayList(&graph[2], 4);
    insertArrayList(&graph[3], 4);
    insertArrayList(&graph[4], 5);
    insertArrayList(&graph[4], 6);
    insertArrayList(&graph[5], 7);
    insertArrayList(&graph[6], 7);

    ArrayList *result = topologicalSort(graph, 7);

    assert(result != NULL);
    assert(result->used == 7);

    bool correctOrder = true;
    correctOrder &= result->array[0] == 1;
    correctOrder &= (result->array[1] == 2 || result->array[1] == 3);
    correctOrder &= (result->array[2] == 2 || result->array[2] == 3);
    correctOrder &= ((result->array[3] == 4 && result->array[4] == 5 && result->array[5] == 6) ||
                     (result->array[3] == 4 && result->array[4] == 6 && result->array[5] == 5));
    correctOrder &= result->array[6] == 7;

    if (!correctOrder) {
        printf("Incorrect order detected:\n");
        for (size_t i = 0; i < result->used; ++i) {
            printf("%zu: %d\n", i, result->array[i]);
        }
    }

    freeArrayList(result);
}

void test_checkCondition_success_no8(void) {
    const int MAX_T = 5;
    ArrayList *sortedTasks = malloc(MAX_T * sizeof(ArrayList));
    for (int i = 0; i < MAX_T; ++i) {
        initArrayList(&sortedTasks[i], 1);
        insertArrayList(&sortedTasks[i], i + 1);
    }

    int Z[MAX_T] = {-1, 2, -3, 4, -5};
    int K = 0;

    int result = checkCondition(sortedTasks, Z, K);

    assert(result == 1);

    for (int i = 0; i < MAX_T; ++i) {
        freeArrayList(&sortedTasks[i]);
    }
    free(sortedTasks);
}

void test_checkCondition_failure_no9(void) {
    const int MAX_T = 5;
    ArrayList *sortedTasks = malloc(MAX_T * sizeof(ArrayList));
    for (int i = 0; i < MAX_T; ++i) {
        initArrayList(&sortedTasks[i], 1);
        insertArrayList(&sortedTasks[i], i + 1);
    }

    int Z[MAX_T] = {1, 2, 3, 4, 5};
    int K = 9;

    int result = checkCondition(sortedTasks, Z, K);

    assert(result == 0);

    for (int i = 0; i < MAX_T; ++i) {
        freeArrayList(&sortedTasks[i]);
    }
    free(sortedTasks);
}

void test_checkCondition_empty_sequence_no10(void) {
    const int MAX_T = 0;
    ArrayList *sortedTasks = malloc(MAX_T * sizeof(ArrayList));

    int Z[MAX_T];
    int K = 0;

    int result = checkCondition(sortedTasks, Z, K);

    assert(result == 1);

    free(sortedTasks);
}
