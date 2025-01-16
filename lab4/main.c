#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sudoku.h"

int main() {
    int grid[GRID_SIZE][GRID_SIZE];
    const char* inputFile = "input.txt";
    const char* outputFile = "output.txt";

    // Чтение входных данных
    readInput(inputFile, grid);

    // Решение Судоку с использованием танцующих ссылок
    bool solved = solveSudokuWithDancingLinks(grid);

    // Запись результата в файл
    writeOutput(outputFile, grid, solved);

    return 0;
}