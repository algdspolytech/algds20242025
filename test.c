#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


#define MAX_N 9

extern int N;
extern int sudoku[MAX_N][MAX_N];
extern bool is_safe(int row, int col, int num);
extern bool solveSudoku();


void is_safe_5alreadyInRow_returnFalse_no1() {
    N = 3;
    int sudoku_test[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = sudoku_test[i][j];
        }
    }

    assert(is_safe(0, 3, 5) == false);

}

void is_safe_5alreadyInColumn_returnFalse_no2() {
    N = 3;
    int sudoku_test[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = sudoku_test[i][j];
        }
    }

    assert(is_safe(6, 0, 5) == false);

}

void is_safe_5alreadyInSquare_returnFalse_no3() {
    N = 3;
    int sudoku_test[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = sudoku_test[i][j];
        }
    }

    assert(is_safe(2, 4, 5) == false);
}

void is_safe_CanBeSet_returnTrue_no4() {
    N = 3;
    int sudoku_test[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = sudoku_test[i][j];
        }
    }

    assert(is_safe(0, 2, 4) == true);

}

void is_safe_NumberBiggerNsqured_returnFalse_no5() {
    N = 3;
    int sudoku_test[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = sudoku_test[i][j];
        }
    }

    assert(is_safe(0, 3, 10) == false);

}

void is_safe_NumberSmaller1_returnFalse_no6() {
    N = 3;
    int sudoku_test[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = sudoku_test[i][j];
        }
    }

    assert(is_safe(0, 3, 0) == false);

}

void is_safe_CellOccupied_returnFalse_no7() {
    N = 3;
    int sudoku_test[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = sudoku_test[i][j];
        }
    }

    assert(is_safe(0, 2, 3) == false);

}

void solveSudoku_ThereIsSolution_returnTrue_no8() {
    N = 3;
    int sudoku_test1[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = sudoku_test1[i][j];
        }
    }

    assert(solveSudoku() == true);
}

void solveSudoku_ThereIsNoSolution_returnFalse_no9() {
    N = 3;
    int sudoku_test1[9][9] = {
        {5, 3, 5, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = sudoku_test1[i][j];
        }
    }

    assert(solveSudoku() == false);
}

void solveSudoku_SudokuNotFull_returnSudokuIsFull_no10() {
    bool is_sudoku_full = true;
    N = 3;
    int sudoku_test1[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = sudoku_test1[i][j];
        }
    }

    solveSudoku();

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] < 1 || sudoku[i][j] > 9)
            {
                is_sudoku_full = false;
            }
        }
    }

    assert(is_sudoku_full == true);
}




void runAllTests() {
    is_safe_5alreadyInRow_returnFalse_no1();
    is_safe_5alreadyInColumn_returnFalse_no2();
    is_safe_5alreadyInSquare_returnFalse_no3();
    is_safe_CanBeSet_returnTrue_no4();
    is_safe_NumberBiggerNsqured_returnFalse_no5();
    is_safe_NumberSmaller1_returnFalse_no6();
    is_safe_CellOccupied_returnFalse_no7();

    solveSudoku_ThereIsSolution_returnTrue_no8();
    solveSudoku_ThereIsNoSolution_returnFalse_no9();
    solveSudoku_SudokuNotFull_returnSudokuIsFull_no10();

    printf("All tests ran successfully!\n");
}