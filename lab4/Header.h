#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#pragma warning (disable : 4996)


#define HEADER_H

// Максимальная длина строки для выражений
#define MAX_LEN 100

// Функция для вычисления значения арифметического выражения
long long eval_expression(const char* expr);

// Рекурсивная функция перебора всех комбинаций
bool solve(const char* A, int B, int index, char* expr, int expr_index);

// Ищет арифметическое выражение, которое дает B
bool find_expression(const char* A, int B, char* result);





