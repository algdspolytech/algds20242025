#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include "lib.h"



int N;
int sudoku[MAX_N][MAX_N];

bool is_safe(int row, int col, int num) 
{
    if (num > N * N)
    {
        return false;
    }

    if (num <= 0)
    {
        return false;
    }

    for (int x = 0; x < N * N; x++) 
    {
        if (sudoku[row][x] == num) 
        {
            return false;
        }
    }


    for (int x = 0; x < N * N; x++) 
    {
        if (sudoku[x][col] == num) 
        {
            return false;
        }
    }


    int startRow = row - row % N;
    int startCol = col - col % N;
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            if (sudoku[i + startRow][j + startCol] == num) 
            {
                return false;
            }
        }
    }
    return true;
}

bool solveSudoku() {
    for (int row = 0; row < N * N; row++) 
    {
        for (int col = 0; col < N * N; col++) 
        {
            if (sudoku[row][col] == 0) 
            {
                for (int num = 1; num <= N * N; num++) 
                {
                    if (is_safe(row, col, num)) 
                    {
                        sudoku[row][col] = num;
                        if (solveSudoku()) 
                        {
                            return true;
                        }
                        sudoku[row][col] = 0; 
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void readInput(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    fscanf(file, "%d", &N);
    for (int i = 0; i < N * N; i++) 
    {
        for (int j = 0; j < N * N; j++) 
        {
            fscanf(file, "%d", &sudoku[i][j]);
        }
    }
    fclose(file);
}

void writeOutput(const char *filename) 
{
    FILE *file = fopen(filename, "w");
    if (solveSudoku()) {
        for (int i = 0; i < N * N; i++) 
        {
            for (int j = 0; j < N * N; j++) 
            {
                fprintf(file, "%d ", sudoku[i][j]);
            }
            fprintf(file, "\n");
        }
    } 
    else 
    {
        fprintf(file, "0");
    }
    fclose(file);
}