#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"  
#include "test.c"

int main() {
    Pair list[MAX_LIST_SIZE];
    int n = 0;

   
    run_tests();

    read_data(list, &n, "data.txt");
  
    qsort(list, n, sizeof(Pair), compare);

    printf("Список слов и ключевых чисел:\n");

    for (int i = 0; i < n; i++) {
        printf("%s %d\n", list[i].word, list[i].key);
    }

  
    int key;
    printf("Введите ключевое число для поиска: ");
    scanf("%d", &key);

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (list[i].key == key) {
            printf("Слово, соответствующее ключу %d:  '%s'\n", key, list[i].word);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Слово, соответствующее ключу %d, не найдено.\n", key);
    }

    return 0;
}

void read_data(Pair* list, int* n, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return;
    }

    char word[MAX_WORD_LENGTH];
    int key;
    while (fscanf(file, "%s %d", word, &key) != EOF) {
        for (int i = 0; i < *n; i++) {
            if (list[i].key == key) {
                printf("Ошибка: Дублирование ключа %d для слова: '%s'\n", key, word);
                fclose(file);
                return;
            }
        }
        strcpy(list[*n].word, word);
        list[*n].key = key;
        (*n)++;
    }
    fclose(file);
}

int compare(const void* a, const void* b) {
    return ((Pair*)a)->key - ((Pair*)b)->key;
}
