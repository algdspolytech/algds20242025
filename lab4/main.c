#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sudoku.h"

int main() {
    int grid[GRID_SIZE][GRID_SIZE];
    const char* inputFile = "input.txt";
    const char* outputFile = "output.txt";

    // ������ ������� ������
    readInput(inputFile, grid);

    // ������� ������ � �������������� ��������� ������
    bool solved = solveSudokuWithDancingLinks(grid);

    // ������ ���������� � ����
    writeOutput(outputFile, grid, solved);

    return 0;
}