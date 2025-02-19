#pragma once
#include <stdio.h>
#include <stdlib.h>


typedef struct Pos {
	int x;
	int y;
} Pos;

typedef struct Board {
	Pos** queens;
	int queens_len;

	int* lines;
	int* 
		
		;
	int* diag_1;
	int* diag_2;

	int N;

} Board;

void LibD(const char* input, const char* output);