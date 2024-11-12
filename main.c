#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 1000  // Максимальный размер доски для избежания переполнения памяти

int board[MAX_N][MAX_N];  // Шахматная доска
int N;  // Размер доски

// Функция для проверки, можно ли поставить ферзя на позицию (row, col)
int isSafe(int row, int col) {
    // Проверка вертикали и диагоналей
    for (int i = 0; i < row; i++) {
        // Проверка по вертикали
        if (board[i][col]) {
            return 0;
        }
        // Проверка по диагонали (слева)
        if (col - (row - i) >= 0 && board[i][col - (row - i)]) {
            return 0;
        }
        // Проверка по диагонали (справа)
        if (col + (row - i) < N && board[i][col + (row - i)]) {
            return 0;
        }
    }
    return 1;  // Позиция безопасна
}


// Рекурсивная функция для расстановки ферзей
int solveNQueens(int row) {
    if (row == N) {
        return 1;  // Все ферзи расставлены
    }
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;  // Ставим ферзя
            if (solveNQueens(row + 1)) {
                return 1;  // Если удалось расставить всех ферзей
            }
            board[row][col] = 0;  // Убираем ферзя 
        }
    }
    return 0;
}

// Функция для сброса доски
void resetBoard(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = 0;
        }
    }
}

// Функция для чтения входных данных и записи результата
void placeQueens() {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("Ошибка открытия файла");
        return;
    }

    fscanf(inputFile, "%d", &N);
    if (N < 1 || N > MAX_N) {
        fprintf(outputFile, "Неверное значение N. Пожалуйста, введите N от 1 до %d.\n", MAX_N);
        fclose(inputFile);
        fclose(outputFile);
        return;
    }

    resetBoard(N);  // Инициализация доски

    if (solveNQueens(0)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j]) {
                    fprintf(outputFile, "%d %d\n", i, j);
                }
            }
        }
    }
    else {
        fprintf(outputFile, "Решение не найдено\n");
    }

    fclose(inputFile);
    fclose(outputFile);
}



// Тест 1: Проверка безопасности для пустой доски
void TestIsSafe_EmptyBoard_no1() {
    N = 4;  // Размер доски
    resetBoard(N);
    assert(isSafe(0, 0) == 1);  // Позиция (0, 0) должна быть безопасной
}

// Тест 2: Проверка безопасности для позиции, где ферзь уже стоит
void TestIsSafe_QueenInColumn_no2() {
    N = 4;
    resetBoard(N);
    board[0][0] = 1;  // Ферзь на (0, 0)
    assert(isSafe(1, 0) == 0);  // Позиция (1, 0) не безопасна
}

// Тест 3: Проверка безопасности для диагонали
void TestIsSafe_QueenInDiagonal_no3() {
    N = 4;
    resetBoard(N);
    board[0][0] = 1;  // Ферзь на (0, 0)
    assert(isSafe(1, 1) == 0);  // Позиция (1, 1) не безопасна
}

// Тест 4: Проверка успешного решения для 4 ферзей
void TestSolveNQueens_Success_no4() {
    N = 4;
    resetBoard(N);
    assert(solveNQueens(0) == 1);  // Должно вернуть 1, если решение существует
}

// Тест 5: Проверка успешного решения для 1 ферзя
void TestSolveNQueens_OneQueen_no5() {
    N = 1;
    resetBoard(N);
    assert(solveNQueens(0) == 1);  // Должно вернуть 1, если решение существует
}

// Тест 6: Проверка неуспешного решения для 2 ферзей
void TestSolveNQueens_Fail_no6() {
    N = 2;
    resetBoard(N);
    assert(solveNQueens(0) == 0);  // Должно вернуть 0, если решения нет
}

// Тест 7: Проверка неуспешного решения для 3 ферзей
void TestSolveNQueens_FailThree_no7() {
    N = 3;
    resetBoard(N);
    assert(solveNQueens(0) == 0);  // Должно вернуть 0, если решения нет
}

// Тест 8: Проверка успешного решения для 8 ферзей
void TestSolveNQueens_EightQueens_no8() {
    N = 8;
    resetBoard(N);
    assert(solveNQueens(0) == 1);  // Должно вернуть 1, если решение существует
}

// Тест 9: Проверка безопасности для позиции, где ферзь бьет по диагонали
void TestIsSafe_QueenInDiagonalAttack_no9() {
    N = 4;
    resetBoard(N);
    board[1][2] = 1;  // Ферзь на (1, 2)
    assert(isSafe(0, 3) == 1);  // Позиция (0, 3) не безопасна
}

// Тест 10: Проверка безопасности для позиции, где ферзь бьет по вертикали
void TestIsSafe_QueenInVerticalAttack_no10() {
    N = 4;
    resetBoard(N);
    board[2][1] = 1;  // Ферзь на (2, 1)
    assert(isSafe(3, 1) == 0);  // Позиция (3, 1) не безопасна
}

int main() {
    TestIsSafe_EmptyBoard_no1();
    TestIsSafe_QueenInColumn_no2();
    TestIsSafe_QueenInDiagonal_no3();
    TestSolveNQueens_Success_no4();
    TestSolveNQueens_OneQueen_no5();
    TestSolveNQueens_Fail_no6();
    TestSolveNQueens_FailThree_no7();
    TestSolveNQueens_EightQueens_no8();
    TestIsSafe_QueenInDiagonalAttack_no9();
    TestIsSafe_QueenInVerticalAttack_no10();

    printf("All tests passed\n");
    return 0;
}