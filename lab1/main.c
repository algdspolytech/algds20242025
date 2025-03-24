#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "tests.h"

#pragma warning(disable : 4996)
#define MAX_WORDS 100
#define MAX_LENGTH 21

// Функция записи в файл
void write_words(const char* filename, char* words[MAX_WORDS * 2], int count) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка записи в файл");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n", words[i]);
    }
    fclose(file);
}

// Функция очистки памяти
void free_words(char* words[MAX_WORDS * 2], int count) {
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    char* words1[MAX_WORDS] = { 0 };
    char* words2[MAX_WORDS] = { 0 };
    char* merged[MAX_WORDS * 2] = { 0 };

    int count1 = read_words("input1.txt", words1);
    int count2 = read_words("input2.txt", words2);
    int merged_count = merge_sorted_lists(words1, count1, words2, count2, merged);

    write_words("output.txt", merged, merged_count);

    // Освобождаем выделенную память
    free_words(words1, count1);
    free_words(words2, count2);
    free_words(merged, merged_count);

    printf("Файл output.txt успешно создан!\n");

    test_read_words_no1();
    test_compare_words_no2();
    test_merge_sorted_lists_no3();
    test_merge_sorted_lists_with_duplicates_no4();
    test_write_words_no5();
    test_merge_empty_lists_no6();
    test_merge_one_empty_list_no7();
    test_merge_identical_lists_no8();
    test_empty_file_no9();
    test_non_existent_file_no10();

    return 0;
}

