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

// ������������ ����� ������ ��� ���������
#define MAX_LEN 100

// ������� ��� ���������� �������� ��������������� ���������
long long eval_expression(const char* expr);

// ����������� ������� �������� ���� ����������
bool solve(const char* A, int B, int index, char* expr, int expr_index);

// ���� �������������� ���������, ������� ���� B
bool find_expression(const char* A, int B, char* result);





