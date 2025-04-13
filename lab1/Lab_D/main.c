#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool* findSubset(unsigned int B, unsigned int N, unsigned int* elements, bool* dp[]) {
    // Инициализация DP таблицы
    for (unsigned int i = 0; i <= N; i++) {
        dp[i][0] = true;
    }

    for (unsigned int i = 1; i <= N; i++) {
        for (unsigned int j = 1; j <= B; j++) {
            if (j < elements[i-1]) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = dp[i-1][j] || dp[i-1][j - elements[i-1]];
            }
        }
    }

    return dp[N][B] ? dp[N] : NULL;
}

void reconstructSubset(unsigned int B, unsigned int N, unsigned int* elements, bool* dp[], FILE* output) {
    if (!dp[N][B]) {
        fprintf(output, "0");
        return;
    }

    unsigned int remaining = B;
    bool first = true;

    for (int i = N; i > 0 && remaining > 0; i--) {
        if (!dp[i-1][remaining]) {
            if (!first) fprintf(output, " ");
            fprintf(output, "%u", elements[i-1]);
            remaining -= elements[i-1];
            first = false;
        }
    }
}

void solveProblem(const char* inputFilename) {
    FILE* input = fopen(inputFilename, "r");
    FILE* output = fopen("output.txt", "w");

    if (!input || !output) {
        if (output) fprintf(output, "0");
        if (input) fclose(input);
        if (output) fclose(output);
        return;
    }

    unsigned int B, N;
    fscanf(input, "%u %u", &B, &N);

    // Явная проверка на B = 0
    if (B == 0) {
        fprintf(output, "0");
        fclose(input);
        fclose(output);
        return;
    }

    unsigned int* elements = malloc(N * sizeof(unsigned int));
    for (unsigned int i = 0; i < N; i++) {
        fscanf(input, "%u", &elements[i]);
    }

    // Выделение памяти для DP таблицы
    bool** dp = malloc((N+1) * sizeof(bool*));
    for (unsigned int i = 0; i <= N; i++) {
        dp[i] = malloc((B+1) * sizeof(bool));
        for (unsigned int j = 0; j <= B; j++) {
            dp[i][j] = false;
        }
        dp[i][0] = true; // Пустая сумма всегда возможна
    }

    // Заполнение DP таблицы
    for (unsigned int i = 1; i <= N; i++) {
        for (unsigned int j = 1; j <= B; j++) {
            if (j < elements[i-1]) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = dp[i-1][j] || dp[i-1][j - elements[i-1]];
            }
        }
    }

    // Восстановление решения
    if (dp[N][B]) {
        unsigned int remaining = B;
        bool first = true;

        for (int i = N; i > 0 && remaining > 0; i--) {
            if (!dp[i-1][remaining]) {
                if (!first) fprintf(output, " ");
                fprintf(output, "%u", elements[i-1]);
                remaining -= elements[i-1];
                first = false;
            }
        }
    } else {
        fprintf(output, "0");
    }

    // Освобождение памяти
    for (unsigned int i = 0; i <= N; i++) {
        free(dp[i]);
    }
    free(dp);
    free(elements);

    fclose(input);
    fclose(output);
}

bool checkOutput(const char* expected) {
    FILE* output = fopen("output.txt", "r");
    if (!output) return false;

    char buffer[1024];
    fgets(buffer, sizeof(buffer), output);
    fclose(output);

    buffer[strcspn(buffer, "\n")] = 0;
    return strcmp(buffer, expected) == 0;
}


// Тест 1: Простой случай с решением
void test1() {
    printf("Test 1: Simple case with solution... ");
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "10\n5\n2 3 4 5 9");
    fclose(input);

    solveProblem("input.txt");

    if (checkOutput("2 3 5") || checkOutput("5 3 2") || checkOutput("3 2 5") ||
        checkOutput("3 5 2") || checkOutput("2 5 3") || checkOutput("5 2 3")) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
}
// Тест 2: Нет решения
void test2() {
    printf("Test 2: No solution... ");
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "7\n3\n2 4 6");
    fclose(input);

    solveProblem("input.txt");

    if (checkOutput("0")) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
}
// Тест 3: Один элемент равен B
void test3() {
    printf("Test 3: Single element equals B... ");
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "5\n3\n1 5 3");
    fclose(input);

    solveProblem("input.txt");

    if (checkOutput("5")) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
}
// Тест 4: Все элементы в сумме дают B
void test4() {
    printf("Test 4: All elements sum to B... ");
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "6\n3\n1 2 3");
    fclose(input);

    solveProblem("input.txt");

    if (checkOutput("1 2 3") || checkOutput("3 2 1") || checkOutput("1 3 2") ||
        checkOutput("2 1 3") || checkOutput("2 3 1") || checkOutput("3 1 2")) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
}
// Тест 5: Пустое множество
void test5() {
    printf("Test 5: Empty set... ");
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "5\n0\n");
    fclose(input);

    solveProblem("input.txt");

    if (checkOutput("0")) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
}
// Тест 6: Большие числа
void test6() {
    printf("Test 6: Large numbers... ");
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "1000000\n4\n200000 300000 400000 500000");
    fclose(input);

    solveProblem("input.txt");

    if (checkOutput("200000 300000 500000") || checkOutput("500000 300000 200000") ||
        checkOutput("200000 500000 300000") || checkOutput("300000 200000 500000") ||
        checkOutput("300000 500000 200000") || checkOutput("500000 200000 300000")) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
}
// Тест 7: Множество с одинаковыми элементами
void test7() {
    printf("Test 7: Set with duplicate elements... ");
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "4\n5\n1 1 2 2 2");
    fclose(input);

    solveProblem("input.txt");

    if (checkOutput("1 1 2") || checkOutput("2 1 1") || checkOutput("1 2 1") ||
        checkOutput("2 2")) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
}

void test8() {
    printf("Test 8: B equals 0 (should return 0)... ");
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "0\n3\n1 2 3");
    fclose(input);

    solveProblem("input.txt");

    if (checkOutput("0")) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
}

void test9() {
    printf("Test 9: Single unique solution (should return 3 4)... ");
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "7\n4\n1 2 3 4");
    fclose(input);

    solveProblem("input.txt");

    // Проверяем оба возможных варианта (3+4 или 1+2+4)
    if (checkOutput("3 4") || checkOutput("4 3") ||
        checkOutput("1 2 4") || checkOutput("4 2 1") ||
        checkOutput("2 1 4") || checkOutput("1 4 2") ||
        checkOutput("2 4 1") || checkOutput("4 1 2")) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
}

void test10() {
    printf("Test 10: Large set with all 1s (sum 1000)... ");
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "1000\n1000\n");
    for (int i = 0; i < 1000; i++) {
        fprintf(input, "1 ");
    }
    fclose(input);

    solveProblem("input.txt");

    // Проверяем что сумма правильная (первые 1000 элементов)
    FILE* output = fopen("output.txt", "r");
    if (!output) {
        printf("FAILED (no output)\n");
        return;
    }

    unsigned int sum = 0;
    unsigned int num;
    int count = 0;
    while (fscanf(output, "%u", &num) == 1) {
        sum += num;
        count++;
    }
    fclose(output);

    if (sum == 1000 && count == 1000) {
        printf("PASSED\n");
    } else {
        printf("FAILED (sum=%u, count=%d)\n", sum, count);
    }
}

int main() {
    // Запуск всех тестов
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();

    return 0;
}
