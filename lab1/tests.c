#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "tests.h"

#define MAX_WORDS 100
#define MAX_LENGTH 21

#pragma warning(disable : 4996)

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Функция сравнения слов для qsort
int compare_words(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

// Функция чтения и сортировки слов из файла
int read_words(const char* filename, char* words[MAX_WORDS]) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return -1;
    }

    int count = 0;
    char buffer[MAX_LENGTH];

    while (count < MAX_WORDS && fscanf(file, "%20s", buffer) == 1) {
        words[count] = strdup(buffer); // Выделяем память для слова
        if (!words[count]) {
            perror("Ошибка выделения памяти");
            fclose(file);
            return count;
        }
        count++;
    }
    fclose(file);

    // Сортировка массива слов
    qsort(words, count, sizeof(char*), compare_words);
    return count;
}

// Заглушка функции чтения слов
void stub_read_words(const char* filename, char words[][MAX_LENGTH], int* count) {
    if (strcmp(filename, "test1.txt") == 0) {
        strcpy(words[0], "apple");
        strcpy(words[1], "banana");
        *count = 2;
    }
    else if (strcmp(filename, "test2.txt") == 0) {
        strcpy(words[0], "cherry");
        strcpy(words[1], "date");
        *count = 2;
    }
}

// Заглушка функции записи слов (имитация работы)
void stub_write_words(const char* filename, char words[][MAX_LENGTH], int count) {
    assert(count == 4);
    assert(strcmp(words[0], "apple") == 0);
    assert(strcmp(words[1], "banana") == 0);
    assert(strcmp(words[2], "cherry") == 0);
    assert(strcmp(words[3], "date") == 0);
}

// Функция объединения двух отсортированных массивов слов
int merge_sorted_lists(char* words1[MAX_WORDS], int count1,
    char* words2[MAX_WORDS], int count2,
    char* merged[MAX_WORDS * 2]) {
    int i = 0, j = 0, k = 0;
    //for (int idx = 0; idx < count1; idx++)
        //printf("words1[%d] = %s\n", idx, words1[idx]);

    //for (int idx = 0; idx < count2; idx++)
        //printf("words2[%d] = %s\n", idx, words2[idx]);
    while (i < count1 && j < count2) {
        //printf("%d ", i); // 0 0 2 2 
        //printf("%d ", j);
        //printf("%s ", words1[i]);
        //printf("%s ", words2[j]);
        //printf("\n");
        int cmp = strcmp(words1[i], words2[j]);
        if (cmp < 0) {
            merged[k++] = strdup(words1[i++]);
        }
        else if (cmp > 0) {
            merged[k++] = strdup(words2[j++]);
        }
        else { // Убираем дубликаты
            merged[k++] = strdup(words1[i++]);
            j++;
        }
    }
    while (i < count1) merged[k++] = strdup(words1[i++]);
    while (j < count2) merged[k++] = strdup(words2[j++]);

    return k; // Количество объединенных слов
}

#endif

// Тест чтения слов (проверка загрузки данных)
void test_read_words_no1() {
    char words[MAX_WORDS][MAX_LENGTH];
    int count = 0;

    stub_read_words("test1.txt", words, &count);
    assert(count == 2);
    assert(strcmp(words[0], "apple") == 0);
    assert(strcmp(words[1], "banana") == 0);

    stub_read_words("test2.txt", words, &count);
    assert(count == 2);
    assert(strcmp(words[0], "cherry") == 0);
    assert(strcmp(words[1], "date") == 0);
    printf("Тест 1 пройден\n");
}

// Тест функции сравнения слов
void test_compare_words_no2() {
    char* word1 = "apple";
    char* word2 = "banana";
    char* word3 = "apple";

    assert(compare_words(&word1, &word2) < 0);
    assert(compare_words(&word2, &word1) > 0);
    assert(compare_words(&word1, &word3) == 0);
    printf("Тест 2 пройден\n");
}

// Тест слияния двух отсортированных списков без дубликатов
void test_merge_sorted_lists_no3() {
    char* words1[MAX_WORDS] = { "apple", "banana" };
    char* words2[MAX_WORDS] = { "cherry", "date" };
    char* merged[MAX_WORDS * 2];
    int merged_count = 0;

    merge_sorted_lists(words1, 2, words2, 2, merged);

    assert(strcmp(merged[0], "apple") == 0);
    assert(strcmp(merged[1], "banana") == 0);
    assert(strcmp(merged[2], "cherry") == 0);
    assert(strcmp(merged[3], "date") == 0);
    printf("Тест 3 пройден\n");
}

// Тест слияния двух отсортированных списков с дубликатами
void test_merge_sorted_lists_with_duplicates_no4() {
    char* words1[MAX_WORDS] = { "apple", "banana", "cherry" };
    char* words2[MAX_WORDS] = { "banana", "cherry", "date" };
    char* merged[MAX_WORDS * 2];

    merge_sorted_lists(words1, 3, words2, 3, merged);

    assert(strcmp(merged[0], "apple") == 0);
    assert(strcmp(merged[1], "banana") == 0);
    assert(strcmp(merged[2], "cherry") == 0);
    assert(strcmp(merged[3], "date") == 0);
    printf("Тест 4 пройден\n");
}

// Тест записи слов в файл
void test_write_words_no5() {
    char words[MAX_WORDS][MAX_LENGTH] = { "apple", "banana", "cherry", "date" };
    stub_write_words("test_output.txt", words, 4);
    printf("Тест 5 пройден\n");
}

// Тест пустых входных данных
void test_merge_empty_lists_no6() {
    char words1[MAX_WORDS][MAX_LENGTH] = {"", ""};
    char words2[MAX_WORDS][MAX_LENGTH] = {"", ""};
    char merged[MAX_WORDS * 2][MAX_LENGTH];
    int merged_count = 0;

    merge_sorted_lists(words1, 0, words2, 0, merged, &merged_count);

    assert(merged_count == 0);
    printf("Тест 6 пройден\n");
}

// Тест, когда один список пуст
void test_merge_one_empty_list_no7() {
    char* words1[MAX_WORDS] = { "apple", "banana" };
    char* words2[MAX_WORDS] = {"", ""};
    char* merged[MAX_WORDS * 2];

    merge_sorted_lists(words1, 2, words2, 0, merged);

    assert(strcmp(merged[0], "apple") == 0);
    assert(strcmp(merged[1], "banana") == 0);
    printf("Тест 7 пройден\n");
}

// Тест на случай, если два списка идентичны
void test_merge_identical_lists_no8() {
    char* words1[MAX_WORDS] = { "apple", "banana" };
    char* words2[MAX_WORDS] = { "apple", "banana" };
    char* merged[MAX_WORDS * 2];

    merge_sorted_lists(words1, 2, words2, 2, merged);

    assert(strcmp(merged[0], "apple") == 0);
    assert(strcmp(merged[1], "banana") == 0);
    printf("Тест 8 пройден\n");
}

// Тест на пустой файл 
void test_empty_file_no9() {
    FILE* file = fopen("empty.txt", "w");  // Создаем пустой файл
    fclose(file);

    char* words[MAX_WORDS];
    int count = read_words("empty.txt", words);

    assert(count == 0);  // Должен быть пустым
    printf("Тест 9 пройден!\n");
}

// Тест на файл с несуществующим названием
void test_non_existent_file_no10() {
    char* words[MAX_WORDS];
    int count = read_words("non_existent.txt", words);

    assert(count == -1);  // Должна возвращаться ошибка (-1)
    printf("Тест 10 пройден\n");
}