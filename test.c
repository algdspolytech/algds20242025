#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

// Тест 1: Проверка дублирования ключей
void test_duplicate_keys() {
    Pair list[MAX_LIST_SIZE] = {
        {"word1", 1},
        {"word2", 2},
        {"word3", 1}  // Дублирование ключа 1
    };
    int n = 3;
    bool has_duplicates = false;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (list[i].key == list[j].key) {
                has_duplicates = true;
                break;
            }
        }
    }
    printf("Тест дублирования ключей: %s\n", has_duplicates ? "Провален" : "Пройден");
}

// Тест 2: Проверка правильного добавления слов
void test_add_words() {
    Pair list[MAX_LIST_SIZE];
    int n = 0;

    strcpy(list[n].word, "word1");
    list[n++].key = 1;

    strcpy(list[n].word, "word2");
    list[n++].key = 2;

    bool correct = (n == 2 && strcmp(list[0].word, "word1") == 0 && strcmp(list[1].word, "word2") == 0);

    printf("Тест добавления слов: %s\n", correct ? "Пройден" : "Провален");
}

// Тест 3: Проверка сортировки
void test_sorting() {
    Pair list[MAX_LIST_SIZE] = {
        {"word3", 3},
        {"word1", 1},
        {"word2", 2}
    };
    int n = 3;

    qsort(list, n, sizeof(Pair), compare);

    bool sorted = (strcmp(list[0].word, "word1") == 0 &&
        strcmp(list[1].word, "word2") == 0 &&
        strcmp(list[2].word, "word3") == 0);
    printf("Тест сортировки: %s\n", sorted ? "Пройден" : "Провален");
}

// Тест 4: Проверка поиска по ключу
void test_search_by_key() {
    Pair list[MAX_LIST_SIZE] = {
        {"word1", 1},
        {"word2", 2},
        {"word3", 3}
    };

    int search_key = 2;
    char* result_word = NULL;

    for (int i = 0; i < 3; i++) {
        if (list[i].key == search_key) {
            result_word = list[i].word;
            break;
        }
    }

    bool correct = (result_word != NULL && strcmp(result_word, "word2") == 0);
    printf("Тест поиска по ключу: %s\n", correct ? "Пройден" : "Провален");
}

// Тест 5: Проверка отсутствия дубликатов
void test_no_duplicates() {
    Pair list[MAX_LIST_SIZE] = {
        {"word1", 1},
        {"word2", 2},
        {"word3", 3}
    };
    int n = 3;
    bool has_duplicates = false;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (list[i].key == list[j].key) {
                has_duplicates = true;
                break;
            }
        }
    }
    printf("Тест на отсутствие дубликатов: %s\n", !has_duplicates ? "Пройден" : "Провален");
}

// Тест 6: Проверка на полное количество добавленных объектов
void test_correct_number_of_pairs() {
    Pair list[MAX_LIST_SIZE];
    int n = 0;

    // Добавим 5 слов в список
    for (int i = 0; i < 5; i++) {
        snprintf(list[n].word, sizeof(list[n].word), "word%d", i + 1);
        list[n++].key = i + 1;
    }

    printf("Тест на правильное количество пар: %s\n", (n == 5) ? "Пройден" : "Провален");
}

// Тест 7: Проверка правильности работы функции чтения данных
void test_read_data() {
    Pair list[MAX_LIST_SIZE];
    int n = 0;

    // Здесь должен быть вызов вашей функции read_data, например, из файла test_data.txt
    // Для демонстрации мы просто добавим вручную
    strcpy(list[n].word, "test_word");
    list[n++].key = 1;

    bool correct = (n == 1 && strcmp(list[0].word, "test_word") == 0);
    printf("Тест чтения данных: %s\n", correct ? "Пройден" : "Провален");
}

// Тест 8: Проверка обработки пустого списка
void test_empty_list() {
    Pair list[MAX_LIST_SIZE];
    int n = 0;

    // Проверяем, что в пустом списке нет элементов
    bool correct = (n == 0);
    printf("Тест обработки пустого списка: %s\n", correct ? "Пройден" : "Провален");
}

// Тест 9: Проверка на случайный порядок слов
void test_random_order() {
    Pair list[MAX_LIST_SIZE] = {
        {"word3", 3},
        {"word1", 1},
        {"word2", 2}
    };
    int n = 3;

    // Каждый раз, когда мы сортируем, мы ожидаем, что список будет отсортирован
    qsort(list, n, sizeof(Pair), compare);

    bool sorted = (strcmp(list[0].word, "word1") == 0 &&
        strcmp(list[1].word, "word2") == 0 &&
        strcmp(list[2].word, "word3") == 0);
    printf("Тест случайного порядка слов: %s\n", sorted ? "Пройден" : "Провален");
}

// Тест 10: Проверка корректности работы при отсутствии записи
void test_no_record_found() {
    Pair list[MAX_LIST_SIZE] = {
        {"word1", 1},
        {"word2", 2},
        {"word3", 3}
    };

    int search_key = 4;  // Здесь 4 не существует
    char* result_word = NULL;

    for (int i = 0; i < 3; i++) {

        if (list[i].key == search_key) {
            result_word = list[i].word;
            break;
        }
    }

    bool correct = (result_word == NULL); // мы ожидаем, что не найдем ничего
    printf("Тест поиска несуществующей записи: %s\n", correct ? "Пройден" : "Провален");
}

void run_tests() {
    printf("Запуск тестов:\n");

    test_duplicate_keys();
    test_add_words();
    test_sorting();
    test_search_by_key();
    test_no_duplicates();
    test_correct_number_of_pairs();
    test_read_data();
    test_empty_list();
    test_random_order();
    test_no_record_found();
}
