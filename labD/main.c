#include <stdio.h>
#include "labD.h"
void isSafe_validPosition_returnTrue_no1();
void isSafe_sameColumn_returnFalse_no2();
void isSafe_sameDiagonal_returnFalse_no3();
void isSafe_validLargeBoard_returnTrue_no4();
void solveNQueensUtil_baseCaseReached_returnTrue_no5();
void solveNQueensUtil_noSolutionBoard_returnFalse_no6();
void solveNQueensUtil_validBoard_returnTrue_no7();
void solveNQueens_correctSolution_returnValidVal_no8();
void solveNQueens_solutionLength_returnValidVal_no9();
void solveNQueens_validSolutionCheck_returnValidVal_no10();
int main() {
    solveNQueensFiles("input.txt", "output.txt");
    printf("Output Success\n");

    isSafe_validPosition_returnTrue_no1();
    isSafe_sameColumn_returnFalse_no2();
    isSafe_sameDiagonal_returnFalse_no3();
    isSafe_validLargeBoard_returnTrue_no4();
    solveNQueensUtil_baseCaseReached_returnTrue_no5();
    solveNQueensUtil_noSolutionBoard_returnFalse_no6();
    solveNQueensUtil_validBoard_returnTrue_no7();
    solveNQueens_correctSolution_returnValidVal_no8();
    solveNQueens_solutionLength_returnValidVal_no9();
    solveNQueens_validSolutionCheck_returnValidVal_no10();

    printf("Tests Success\n");

    return 0;
}