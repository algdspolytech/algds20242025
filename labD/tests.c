#include <assert.h>
#include "labD.h"

// тест 1
void isSafe_validPosition_returnTrue_no1() {
    int board[4] = { 1, 3 };
    assert(isSafe(board, 2, 0, 4) == 1);
}

// тест 2
void isSafe_sameColumn_returnFalse_no2() {
    int board[4] = { 0 };
    assert(isSafe(board, 1, 0, 4) == 0);
}

// тест 3
void isSafe_sameDiagonal_returnFalse_no3() {
    int board[4] = { 1 };
    assert(isSafe(board, 1, 2, 4) == 0);
}

// тест 4
void isSafe_validLargeBoard_returnTrue_no4() {
    int board[8] = { 0, 4, 7, 5, 2 };
    assert(isSafe(board, 5, 6, 8) == 1);
}

// тест 5
void solveNQueensUtil_baseCaseReached_returnTrue_no5() {
    int board[1] = { -1 };
    assert(solveNQueensUtil(board, 1, 1) == 1);
}

// тест 6
void solveNQueensUtil_noSolutionBoard_returnFalse_no6() {
    int board[3] = { -1, -1, -1 };
    assert(solveNQueensUtil(board, 0, 3) == 0);
}

// тест 7
void solveNQueensUtil_validBoard_returnTrue_no7() {
    int board[4] = { -1, -1, -1, -1 };
    assert(solveNQueensUtil(board, 0, 4) == 1);
}

// тест 8
void solveNQueens_correctSolution_returnValidVal_no8() {
    int solution[4] = { -1, -1, -1, -1 };
    solveNQueens(4, solution);
    assert(solution[0] >= 0 && solution[0] < 4);
}

// тест 9
void solveNQueens_solutionLength_returnValidVal_no9() {
    int solution[5] = { -1, -1, -1, -1, -1 };
    solveNQueens(5, solution);
    assert(solution[4] >= 0 && solution[4] < 5);
}

// тест 10
void solveNQueens_validSolutionCheck_returnValidVal_no10() {
    int solution[8];
    solveNQueens(8, solution);
    assert(solution[7] >= 0 && solution[7] < 8);
}