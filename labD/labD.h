#ifndef LABD_H
#define LABD_H

int isSafe(int* board, int row, int col, int N); // ���������, ��������� �� ������ �� ����� board
int solveNQueensUtil(int* board, int row, int N); 
void solveNQueensFiles(const char* input_filename, const char* output_filename);
void solveNQueens(int N, int* solution);

#endif