#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include "lib.h"
#include "tests.h"

int N;
int sudoku[MAX_N][MAX_N];

int main() 
{
    runAllTests();
    readInput("input.txt");
    writeOutput("output.txt");
    return 0;
}
