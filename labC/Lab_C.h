#pragma once

#ifndef LAB_C_H
#define LAB_C_H
#ifdef __cplusplus  
extern "C" {
#endif  

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


    // ���������� �������
    int** readMatrix(const char* filename, int* rows, int* cols);
    int** createAdjacencyList(int** matrix, int rows, int cols, int** adjacencySizes);
    void writeAdjacencyListToFile(const char* filename, int** adjacencyList, int* adjacencySizes, int rows);


#ifdef __cplusplus  
}
#endif  

#endif // LAB_C_H
