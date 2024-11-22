﻿#pragma once


typedef enum Flag_t {
	NO,
	YES
} Flag_t;


int CheckPos(Flag_t** board, int i, int j, int size);


int FindSolution(int n, Flag_t** board, int m);


int NQueens(char* inputFilename, char* outputFilename);