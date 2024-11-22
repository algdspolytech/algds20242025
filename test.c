#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "main.h"
#include "test.h"


Flag_t** createBoard(int n, const int queenPositions[][2], int numQueens) {
    Flag_t** board = (Flag_t**)malloc(n * sizeof(Flag_t*));
    for (int i = 0; i < n; ++i) {
        board[i] = (Flag_t*)malloc(n * sizeof(Flag_t));
        for (int j = 0; j < n; ++j) {
            board[i][j] = NO;
        }
    }
    for (int i = 0; i < numQueens; ++i) {
        board[queenPositions[i][0]][queenPositions[i][1]] = YES;
    }
    return board;
}


void deleteBoard(Flag_t** board, int n) {
    for (int i = 0; i < n; ++i) free(board[i]);
    free(board);
}

void runTest(bool result, const char* testName) {
    printf("%s: %s\n", testName, result ? "PASS" : "FAIL");
}

bool testIsSafe1() { return isSafe(createBoard(4, (int[][2]){}, 0), 0, 0, 4); }
bool testIsSafe2() { int pos[][2] = {{0, 0}}; return !isSafe(createBoard(4, pos, 1), 0, 1, 4); }
bool testIsSafe3() { int pos[][2] = {{1, 0}}; return !isSafe(createBoard(4, pos, 1), 2, 1, 4); }
bool testIsSafe4() { int pos[][2] = {{1, 2}}; return !isSafe(createBoard(4, pos, 1), 0, 1, 4); }
bool testIsSafe5() { int pos[][2] = {{0, 0}, {1, 2}, {2, 3}, {3, 1}}; return isSafe(createBoard(4, pos, 4), 2, 3, 4); }


bool testSolveNQueens1() {
    FILE* fp = fopen("test_input.txt", "w");
    fprintf(fp, "4");
    fclose(fp);
    bool result = solveNQueens("test_input.txt", "test_output.txt") == 1;
    remove("test_input.txt");
    remove("test_output.txt");
    return result;
}

bool testSolveNQueens2() {
    FILE* fp = fopen("test_input.txt", "w");
    fprintf(fp, "2");
    fclose(fp);
    bool result = solveNQueens("test_input.txt", "test_output.txt") == 0;
    remove("test_input.txt");
    remove("test_output.txt");
    return result;
}

bool testMemoryAllocation1() {
    Flag_t** board = createBoard(10, (int[][2]){}, 0);
    bool result = board != NULL;
    deleteBoard(board, 10);
    return result;
}

bool testMemoryAllocation2() {
    Flag_t** board = createBoard(0, (int[][2]){}, 0);
    bool result = board == NULL; 
    if (board != NULL) deleteBoard(board, 0);
    return result;
}

bool testFileOpenError() {
    return solveNQueens("nonexistentfile.txt", "test_output.txt") == 0;
}

bool testInvalidInputFile() {
    FILE* fp = fopen("test_input.txt", "w");
    fprintf(fp, "abc");
    fclose(fp);
    bool result = solveNQueens("test_input.txt", "test_output.txt") == 0;
    remove("test_input.txt");
    remove("test_output.txt");
    return result;
}

int main() {
    runTest(testIsSafe1(), "isSafe_Test_1_Empty_Board");
    runTest(testIsSafe2(), "isSafe_Test_2_Row_Conflict");
    runTest(testIsSafe3(), "isSafe_Test_3_Diagonal1_Conflict");
    runTest(testIsSafe4(), "isSafe_Test_4_Diagonal2_Conflict");
    runTest(testIsSafe5(), "isSafe_Test_5_Complex_Safe");
    runTest(testSolveNQueens1(), "solveNQueens_Test_6_4x4");
    runTest(testSolveNQueens2(), "solveNQueens_Test_7_2x2_NoSolution");
    runTest(testMemoryAllocation1(), "MemoryAllocation_Test_8_10x10");
    runTest(testMemoryAllocation2(), "MemoryAllocation_Test_9_0x0");
    runTest(testFileOpenError(), "FileOpenError_Test_10_NonExistentFile");
    runTest(testInvalidInputFile(), "InvalidInput_Test_11_InvalidInput");
    return 0;
}