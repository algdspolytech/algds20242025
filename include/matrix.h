#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	unsigned int height;
	unsigned int width;
	int** elems;
}matrix;

matrix* Parse(const char*);
char* ReadFile(const char*);


#endif 