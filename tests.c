#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "tree.h"

void runTest(const char* input, const char* expectedOutput, int i) {
    FILE* inputFile = fopen("input.txt", "w");
    if (inputFile == NULL) {
        perror("Ошибка открытия input.txt");
        return;
    }
    fprintf(inputFile, "%s", input);
    fclose(inputFile);

    execute_algorithm();

    FILE* outputFile = fopen("output.txt", "r");
    if (outputFile == NULL) {
        perror("Ошибка открытия output.txt");
        return;
    }

    size_t outputSize = 512;
    char* output = (char*)malloc(outputSize);
    if (output == NULL) {
        perror("Ошибка выделения памяти");
        fclose(outputFile);
        return;
    }

    // Чтение результата из файла
    size_t bytesRead = fread(output, sizeof(char), outputSize - 1, outputFile);
    output[bytesRead] = '\0'; // Завершаем строку нулевым символом
    fclose(outputFile);

    if (strcmp(output, expectedOutput) == 0) {
        printf("Тест %d пройден\n", i);
    }
    else {
        printf("Тест %d не пройден!\n", i);
        printf("Ожидали: %s\n", expectedOutput);
        printf("Получили: %s\n", output);
    }
    free(output);
}

int main() {
    setlocale(LC_ALL, "RUS");

    // Тест 1: Пустое дерево
    runTest("", "", 1);

    // Тест 2: Одно слово
    runTest("hello\n", "hello\n5\n", 2);

    // Тест 3: Дерево с двумя узлами
    runTest("hello\nworld\n", "hello\n5\nworld\n5\n", 3);

    // Тест 4: Балансированное дерево
    runTest("cat\ndog\nfish\n", "cat\n3\ndog\n3\nfish\n4\n", 4);

    // Тест 5: Не сбалансированное дерево
    runTest("a\nab\nabc\nabcd\n", "a\n1\nab\n2\nabc\n3\nabcd\n4\n", 5);

    // Тест 6: Дерево с одинаковыми длинами слов
    runTest("one\ntwo\nred\nblue\n", "blue\n4\none\n3\nred\n3\ntwo\n3\n", 6);

    // Тест 7: Смешанное дерево
    runTest("apple\norange\nbanana\nkiwi\n", "apple\n5\nbanana\n6\nkiwi\n4\norange\n6\n", 7);

    // Тест 8: Тест с пробелами в словах
    runTest("hello world\ntest case\n", "hello world\n11\ntest case\n9\n", 8);

    // Тест 9: Дерево с пулями
    runTest("!@#$%\n^&*()_+\n", "!@#$%\n5\n^&*()_+\n7\n", 9);

    // Тест 10: Большое дерево
    runTest("medium\nverylongword\nshort\ntiny\nthequickbrownfox\n",
        "medium\n6\nshort\n5\nthequickbrownfox\n16\ntiny\n4\nverylongword\n12\n", 10);

    // Тест 11 (из README)
    runTest("cat\ndog\nfish\n", "cat\n3\ndog\n3\nfish\n4\n", 11);

    return 0;
}
