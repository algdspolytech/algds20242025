#ifndef TESTS_H
#define TESTS_H
#include "lib.h"
#include <assert.h>

void runAllTests();

void is_safe_5alreadyInRow_returnFalse_no1();
void is_safe_5alreadyInColumn_returnFalse_no2();
void is_safe_5alreadyInSquare_returnFalse_no3();
void is_safe_CanBeSet_returnTrue_no4();
void is_safe_NumberBiggerNsqured_returnFalse_no5();
void is_safe_NumberSmaller1_returnFalse_no6();
void is_safe_CellOccupied_returnFalse_no7();

void solveSudoku_ThereIsSolution_returnTrue_no8();
void solveSudoku_ThereIsNoSolution_returnFalse_no9();
void solveSudoku_SudokuNotFull_returnSudokuIsFull_no10();