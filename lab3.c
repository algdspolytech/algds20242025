//
// Created by Александр on 02.11.2024.
//
#define _CRT_SECURE_NO_WARNINGS
#include "lab3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool read_tasks(const char* filename, Task* tasks, int* task_count, int* K) {
    FILE* file = fopen(filename, "r");
    if (!file) return false;

    fscanf(file, "%d %d", task_count, K);
    for (int i = 0; i < *task_count; i++) {
        fscanf(file, "%d", &tasks[i].cost);
        tasks[i].id = i + 1;
    }

    fclose(file);
    return true;
}

bool process_schedule(const Task* tasks, int task_count, int K, int* result_schedule) {

    int total_cost = 0;
    for (int i = 0; i < task_count; i++) {
        total_cost += tasks[i].cost;
        if (total_cost > K) return false;
        result_schedule[i] = tasks[i].id;
    }
    return true;
}

void write_schedule(const char* filename, const int* schedule, int task_count) {

    FILE* file = fopen(filename, "w");
    if (!file) return;

    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%d ", schedule[i]);
    }
    fprintf(file, "\n");
    fclose(file);
}