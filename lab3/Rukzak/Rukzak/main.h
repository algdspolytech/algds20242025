#pragma once
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

void read_input(const char* filename, int* U, int* B, int* K, int** weights, int** values);
void write_output(const char* filename, int* selected_items, int count);
int knapsack(int U, int B, int K, int* weights, int* values);

#endif // MAIN_H
