#pragma once
#include <stdio.h>
#include <stdlib.h>

void read_input(const char* filename, int* U, int* B, int* K, int** weights, int** values);
void write_output(const char* filename, int* selected_items, int count);
int knapsack(int U, int B, int K, const int* weights, const int* values);
