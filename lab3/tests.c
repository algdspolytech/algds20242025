#include <assert.h>
#include "functions.h"

void test_is_safe() {
    //корректная расстановки для N=4
    int positions[4] = { 1, 3, 0, 2 }; 
    assert(is_safe(3, 2, positions) == 1); 
    assert(is_safe(3, 1, positions) == 0);

    // Пустая доска
    int positions_empty[4] = { -1, -1, -1, -1 }; 
    assert(is_safe(0, 0, positions_empty) == 1);
    assert(is_safe(0, 3, positions_empty) == 1);
}

void test_solve_n_queens() {
    int positions[4];
    assert(solve_n_queens(4, positions) == 1);

    int positions_fail[3];
    assert(solve_n_queens(3, positions_fail) == 0); 

    int positions_1[1];
    assert(solve_n_queens(1, positions_1) == 1);

    int positions_zero;
    assert(solve_n_queens(0, &positions_zero) == 0);

    int positions_large_boundary;
    assert(solve_n_queens(1000000, &positions_large_boundary) == 0);
}

void TESTS() {
    test_is_safe();
    test_solve_n_queens();
}
