#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX_DIGITS 100
#define MAX_EXPRESSION 250

char* merge(char* exp);
long long calculate(char* expression);
char* insert_operator(char* expression, char op, int index_place);
int generate_expressions(char* A, int B, FILE* output);
bool check_A(char* A);
