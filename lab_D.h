#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 9

bool is_safe(int row, int col, int num);

bool solveSudoku();

void readInput(const char *filename); 

void writeOutput(const char *filename); 