// Lab_C.h : включаемый файл дл€ стандартных системных включаемых файлов
// или включаемые файлы дл€ конкретного проекта.

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


    // ќбъ€влени€ функций
    int** readMatrix(const char* filename, int* rows, int* cols);
    int** createAdjacencyList(int** matrix, int rows, int cols, int** adjacencySizes);
    void writeAdjacencyListToFile(const char* filename, int** adjacencyList, int* adjacencySizes, int rows);


#ifdef __cplusplus  
}
#endif  

#endif // LAB_C_H