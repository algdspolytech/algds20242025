#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 1000  // ������������ ������ ����� ��� ��������� ������������ ������

int board[MAX_N][MAX_N];  // ��������� �����
int N;  // ������ �����

// ������� ��� ��������, ����� �� ��������� ����� �� ������� (row, col)
int isSafe(int row, int col) {
    // �������� ��������� � ����������
    for (int i = 0; i < row; i++) {
        // �������� �� ���������
        if (board[i][col]) {
            return 0;
        }
        // �������� �� ��������� (�����)
        if (col - (row - i) >= 0 && board[i][col - (row - i)]) {
            return 0;
        }
        // �������� �� ��������� (������)
        if (col + (row - i) < N && board[i][col + (row - i)]) {
            return 0;
        }
    }
    return 1;  // ������� ���������
}


// ����������� ������� ��� ����������� ������
int solveNQueens(int row) {
    if (row == N) {
        return 1;  // ��� ����� �����������
    }
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;  // ������ �����
            if (solveNQueens(row + 1)) {
                return 1;  // ���� ������� ���������� ���� ������
            }
            board[row][col] = 0;  // ������� ����� 
        }
    }
    return 0;
}

// ������� ��� ������ �����
void resetBoard(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = 0;
        }
    }
}

// ������� ��� ������ ������� ������ � ������ ����������
void placeQueens() {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("������ �������� �����");
        return;
    }

    fscanf(inputFile, "%d", &N);
    if (N < 1 || N > MAX_N) {
        fprintf(outputFile, "�������� �������� N. ����������, ������� N �� 1 �� %d.\n", MAX_N);
        fclose(inputFile);
        fclose(outputFile);
        return;
    }

    resetBoard(N);  // ������������� �����

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
        fprintf(outputFile, "������� �� �������\n");
    }

    fclose(inputFile);
    fclose(outputFile);
}



// ���� 1: �������� ������������ ��� ������ �����
void TestIsSafe_EmptyBoard_no1() {
    N = 4;  // ������ �����
    resetBoard(N);
    assert(isSafe(0, 0) == 1);  // ������� (0, 0) ������ ���� ����������
}

// ���� 2: �������� ������������ ��� �������, ��� ����� ��� �����
void TestIsSafe_QueenInColumn_no2() {
    N = 4;
    resetBoard(N);
    board[0][0] = 1;  // ����� �� (0, 0)
    assert(isSafe(1, 0) == 0);  // ������� (1, 0) �� ���������
}

// ���� 3: �������� ������������ ��� ���������
void TestIsSafe_QueenInDiagonal_no3() {
    N = 4;
    resetBoard(N);
    board[0][0] = 1;  // ����� �� (0, 0)
    assert(isSafe(1, 1) == 0);  // ������� (1, 1) �� ���������
}

// ���� 4: �������� ��������� ������� ��� 4 ������
void TestSolveNQueens_Success_no4() {
    N = 4;
    resetBoard(N);
    assert(solveNQueens(0) == 1);  // ������ ������� 1, ���� ������� ����������
}

// ���� 5: �������� ��������� ������� ��� 1 �����
void TestSolveNQueens_OneQueen_no5() {
    N = 1;
    resetBoard(N);
    assert(solveNQueens(0) == 1);  // ������ ������� 1, ���� ������� ����������
}

// ���� 6: �������� ����������� ������� ��� 2 ������
void TestSolveNQueens_Fail_no6() {
    N = 2;
    resetBoard(N);
    assert(solveNQueens(0) == 0);  // ������ ������� 0, ���� ������� ���
}

// ���� 7: �������� ����������� ������� ��� 3 ������
void TestSolveNQueens_FailThree_no7() {
    N = 3;
    resetBoard(N);
    assert(solveNQueens(0) == 0);  // ������ ������� 0, ���� ������� ���
}

// ���� 8: �������� ��������� ������� ��� 8 ������
void TestSolveNQueens_EightQueens_no8() {
    N = 8;
    resetBoard(N);
    assert(solveNQueens(0) == 1);  // ������ ������� 1, ���� ������� ����������
}

// ���� 9: �������� ������������ ��� �������, ��� ����� ���� �� ���������
void TestIsSafe_QueenInDiagonalAttack_no9() {
    N = 4;
    resetBoard(N);
    board[1][2] = 1;  // ����� �� (1, 2)
    assert(isSafe(0, 3) == 1);  // ������� (0, 3) �� ���������
}

// ���� 10: �������� ������������ ��� �������, ��� ����� ���� �� ���������
void TestIsSafe_QueenInVerticalAttack_no10() {
    N = 4;
    resetBoard(N);
    board[2][1] = 1;  // ����� �� (2, 1)
    assert(isSafe(3, 1) == 0);  // ������� (3, 1) �� ���������
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