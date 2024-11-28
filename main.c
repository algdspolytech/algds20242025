#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

#pragma warning(disable:4996) 
#define _CRT_SECURE_NO_WARNINGS 
#define _USE_MATH_DEFINES 
#define _CRTDBG_MAP_ALLOC 


#define MAX_N 15 // Устанавливаем максимальное значение N для тестирования

int board[MAX_N][MAX_N];
int N;

void resetBoard(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = 0;
        }
    }
}

int isSafe(int row, int col) {
    // Проверка строки
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return 0;

    // Проверка верхней диагонали
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    // Проверка нижней диагонали
    for (int i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return 0;
    return 1;
}

int solveNQueensUtil(int col) {
    if (col >= N)
        return 1;

    for (int i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;

            if (solveNQueensUtil(col + 1))
                return 1;

            board[i][col] = 0; // Backtrack
        }
    }
    return 0;
}

void solveNQueens(int N) {
    resetBoard(N);

    if (solveNQueensUtil(0)) {
        FILE* outputFile = fopen("output.txt", "w");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == 1) {
                    fprintf(outputFile, "%d %d\n", i, j);
                }
            }
        }
        fclose(outputFile);
    }
    else {
        printf("Решение не найдено\n");
    }
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    fscanf(inputFile, "%d", &N);
    fclose(inputFile);

    if (N >= 0 && N < MAX_N) {
        solveNQueens(N);
    }
    else {
        printf("Значение N должно быть от 0 до %d\n", MAX_N - 1);
    }

    return 1;
}

void SolveFor1_no1() {
    N = 1;
    resetBoard(1);
    assert(isSafe(0,0) == 1);
}

void SolveFor2_no2() {
    N = 2;
    resetBoard(2);
    assert(solveNQueensUtil(0) == 1);
}

void SolveFor3_no3() {
    N = 3;
    resetBoard(3);
    assert(solveNQueensUtil(0) == 0);
}

void SolveFor4_no4() {
    N = 4;
    resetBoard(4);
    assert(solveNQueensUtil(0) == 1);
}

void TestIsSafe_no5() {
    N = 5;
    resetBoard(5);
    int result[5][2] = { {0, 0}, {1, 3}, {2, 1}, {3, 4}, {4, 2} }; // solve
    assert(isSafe(0,1) == 1);
    assert(isSafe(1, 3) == 1);
    assert(isSafe(2, 0) == 1);
    assert(isSafe(3, 4) == 1);
    assert(isSafe(4, 2) == 1);
}

void VerticalAttack_no6() {
    N = 8;
    resetBoard(8);
    board[4][3] = 1;
    assert(isSafe(5,3) == 0);
}

void DiagonalAttack_no7() {
    N = 7;
    resetBoard(7);
    board[4][4] = 1;
    assert(isSafe(1,1) == 0);
}

void HorizontalAttack_no8() {
    N = 8;
    resetBoard(8);
    board[2][3] = 1;
    assert(isSafe(2,6) == 0);
}


void DiagonalAttack_no9() {
    N = 6;
    resetBoard(N);
    board[1][1] = 1;
    assert(isSafe(3,4) == 1);
}

void SolveFor_MAX_N_no10() {
    N = 15;
    resetBoard(N);
    assert(solveNQueensUtil(0) == 1);
}


void runAllTests() {
    void SolveFor1_no1();
    void SolveFor2_no2();
    void SolveFor3_no3();
    void SolveFor4_no4();
    void TestIsSafe_no5();
    void VerticalAttack_no6();
    void DiagonalAttack_no7();
    void HorizontalAttack_no8();
    void DiagonalAttack_no9();
    void SolveFor_MAX_N_no10();
    printf("Все тесты выполнены успешно.\n");
}