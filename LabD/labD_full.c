#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// Проверка доступности элемента с учетом зависимостей
int isTaskAvailable(int task, int** deps, int* status, int taskCount) {
    for (int i = 0; i < taskCount; i++) {
        if (deps[i][0] == task && status[deps[i][1]] == 1) {
            return 0; 
    }
    return 1; 
}

// Возврат на шаг назад в рекурсии
void undoTask(int* count, int* totalTime, int* status, int* taskTimes, int taskIndex) {
    (*count)--;
    (*totalTime) -= taskTimes[taskIndex];
    status[taskIndex] = 0;
}

// Добавление символа к строке
void appendToString(char** str, char character) {
    if (*str == NULL) {
        *str = malloc(2); 
        (*str)[0] = character;
        (*str)[1] = '\0';
        return;
    }

    int length = strlen(*str);
    *str = realloc(*str, length + 2); 
    (*str)[length + 1] = '\0';
}

// Печать строки в обратном порядке
void printReversed(const char* str) {
    if (str == NULL) return;
    for (int i = strlen(str) - 1; i >= 0; i--) {
        printf("%c", str[i]);
    }
}

// Преобразование целого числа в строку
void numberToString(int number, char* str) {
    sprintf(str, "%d", abs(number));
}

// Рекурсивный поиск комбинаций задач
int exploreCombinations(int totalTasks, int maxTime, int minLeft, int depCount,
    int** dependencies, int* status, int* taskTimes,
    int currentTask, int* selectedCount, int* currentSum,
    int* maxAchieved, char** result) {

    status[currentTask] = 1;
    (*selectedCount)++;
    (*currentSum) += taskTimes[currentTask];

    if (*currentSum > maxTime) {
        undoTask(selectedCount, currentSum, status, taskTimes, currentTask);
        return 0; // Превышено время
    }

    if (isTaskAvailable(currentTask, dependencies, status, depCount)) {
        for (int i = 0; i < totalTasks; i++) {
            if (status[i] == 0) {
                exploreCombinations(totalTasks, maxTime, minLeft, depCount,
                    dependencies, status, taskTimes, i,
                    selectedCount, currentSum, maxAchieved, result);
            }
        }
        if (*selectedCount < (totalTasks - minLeft)) {
            undoTask(selectedCount, currentSum, status, taskTimes, currentTask);
            return 0;
        }
    }
    else {
        undoTask(selectedCount, currentSum, status, taskTimes, currentTask);
        return 0;
    }

    char buffer[10];
    numberToString(currentTask + 1, buffer);
    for (int i = 0; buffer[i] != '\0'; i++) {
        appendToString(result, buffer[i]);
    }
    appendToString(result, ' ');

    return 1;
}

// Тестовые функции
void test_numberToString() {
    char buffer[10];
    numberToString(123, buffer);
    assert(strcmp(buffer, "123") == 0);

    numberToString(-456, buffer);
    assert(strcmp(buffer, "456") == 0);
}

void test_appendToString() {
    char* testStr = NULL;
    appendToString(&testStr, 'A');
    assert(strcmp(testStr, "A") == 0);

    appendToString(&testStr, 'B');
    assert(strcmp(testStr, "AB") == 0);
    free(testStr);
}

void runTests() {
    test_numberToString();
    test_appendToString();
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }

    int totalTasks, maxTime, minLeft;
    fscanf(inputFile, "%d %d %d", &totalTasks, &maxTime, &minLeft);

    int* taskTimes = calloc(totalTasks, sizeof(int));
    for (int i = 0; i < totalTasks; i++) {
        fscanf(inputFile, "%d", &taskTimes[i]);
    }

    int depCount;
    fscanf(inputFile, "%d", &depCount);
    int** dependencies = calloc(depCount, sizeof(int*));
    for (int i = 0; i < depCount; i++) {
        dependencies[i] = calloc(2, sizeof(int));
        fscanf(inputFile, "%d %d", &dependencies[i][0], &dependencies[i][1]);
        dependencies[i][0]--;
        dependencies[i][1]--;
    }

    int* status = calloc(totalTasks, sizeof(int));
    char* result = NULL;

    int selectedCount = 0, currentSum = 0, maxAchieved = 0;
    exploreCombinations(totalTasks, maxTime, minLeft, depCount, dependencies,
        status, taskTimes, 0, &selectedCount, &currentSum,
        &maxAchieved, &result);

    if (result == NULL || strlen(result) == 0) {
        printf("0\n");
    }
    else {
        printReversed(result);
    }

    // Освобождение памяти
    free(taskTimes);
    for (int i = 0; i < depCount; i++) {
        free(dependencies[i]);
    }
    free(dependencies);
    free(status);
    free(result);

    fclose(inputFile);
    runTests();

    return 0;
}
