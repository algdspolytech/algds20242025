#include "labD.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Макрос для проведения тестов
#define ASSERT_TRUE(condition, test_name) \
    if (!(condition)) { \
        printf("%s: FAIL\n", test_name); \
        return false; \
    } else { \
        printf("%s: PASS\n", test_name); \
    }

// Тест 1: N = 1 (Минимальный случай)
bool TestSolveNQueens_SingleQueen_no1() {
    int N = 1;
    int solution[1];
    bool result = solve_n_queens(N, solution);
    ASSERT_TRUE(result, "TestSolveNQueens_SingleQueen_no1");
    
    return true;
}

// Тест 2: N = 4 (Стандартный случай)
bool TestSolveNQueens_N4_no2() {
    int N = 4;
    int solution[4];
    bool result = solve_n_queens(N, solution);
    ASSERT_TRUE(result, "TestSolveNQueens_N4_no2");
    
    return true;
}

// Тест 3: N = 0 (Крайний случай)
bool TestSolveNQueens_N0_no3() {
    int N = 0;
    int* solution = NULL;
    bool result = solve_n_queens(N, solution);
    ASSERT_TRUE(result, "TestSolveNQueens_N0_no3");
    return true;
}

// Тест 4: N = 2 (Нет решения)
bool TestSolveNQueens_N2_no4() {
    int N = 2;
    int solution[2];
    bool result = solve_n_queens(N, solution);
    ASSERT_TRUE(result, "TestSolveNQueens_N2_no4");
    return true;
}

// Тест 5: N = 8 (Стандартный случай)
bool TestSolveNQueens_N8_no5() {
    int N = 8;
    int solution[8];
    bool result = solve_n_queens(N, solution);
    ASSERT_TRUE(result, "TestSolveNQueens_N8_no5");
    
    return true;
}

// Тест 6: N = 3 (Нет решения)
bool TestSolveNQueens_N3_no6() {
    int N = 3;
    int solution[3];
    bool result = solve_n_queens(N, solution);
    ASSERT_TRUE(!result, "TestSolveNQueens_N3_no6");
    return true;
}

// Тест 7: N = -5 (отрицательное число)
bool TestSolveNQueens_N5_no7() {
    int N = -5;
    int solution[5];
    bool result = solve_n_queens(N, solution);
    ASSERT_TRUE(result, "TestSolveNQueens_N5_no7");
    
    return true;
}

// Тест 8: N = 10 (Средний случай)
bool TestSolveNQueens_N10_no8() {
    char N = 10;
    int solution[10];
    bool result = solve_n_queens(N, solution);
    ASSERT_TRUE(result, "TestSolveNQueens_N10_no8");
    
    return true;
}

// Тест 9: N = 9999000 (Большой размер)
bool TestSolveNQueens_LargeN_no9() {
    int N = 9999000; 
    int* solution = (int*)malloc(N * sizeof(int));
    if (!solution) {
        printf("TestSolveNQueens_LargeN_no9: FAIL (Memory Allocation)\n");
        return false;
    }
    bool result = solve_n_queens(N, solution);
    ASSERT_TRUE(result, "TestSolveNQueens_LargeN_no9");
    free(solution);
    return true;
}

// Тест 10: N = 7 (Чистый случай)
bool TestSolveNQueens_N7_no10() {
    int N = 7;
    int solution[7];
    bool result = solve_n_queens(N, solution);
    ASSERT_TRUE(result, "TestSolveNQueens_N7_no10");
    
    return true;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int N = read_input("C:/input.txt");
    if (N < 0 || N >= 1000000) {
        fprintf(stderr, "Некорректное значение N: %d\n", N);
        return 1;
    }

    // Выделение памяти для решения
    int* solution = (int*)malloc(N * sizeof(int));
    if (!solution) {
        perror("Не удалось выделить память");
        return 1;
    }

    if (solve_n_queens(N, solution)) {
        if (!write_output("output.txt", solution, N)) {
            free(solution);
            return 1;
        }
    }
    else {
        fprintf(stderr, "Решение не найдено для N = %d\n", N);
        free(solution);
        return 1;
    }

    free(solution);

    printf("Запуск тестов...\n\n");
    TestSolveNQueens_SingleQueen_no1();
    TestSolveNQueens_N4_no2();
    TestSolveNQueens_N0_no3();
    TestSolveNQueens_N2_no4();
    TestSolveNQueens_N8_no5();
    TestSolveNQueens_N3_no6();
    TestSolveNQueens_N5_no7();
    TestSolveNQueens_N10_no8();
    TestSolveNQueens_LargeN_no9();
    TestSolveNQueens_N7_no10();

    printf("\nТестирование завершено.\n");
    return 0;
}
