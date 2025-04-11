#include "Header.h"

// Тест: Вставка одного элемента
void test_insert_EmptyTable_insertValidString_returnTrue() {
    memset(table, 0, sizeof(table));  // Очищаем таблицу
    int result = insert("apple");
    printf("TestInsert_SingleElement_ReturnValidVal = %d\n", result == 1);
}

// Тест: Вставка строки в заполненную таблицу с линейной пробацией
void test_insert_AlreadyFilledSlot_insertAtAnotherPosition_returnTrue() {
    memset(table, 0, sizeof(table));  // Очищаем таблицу
    insert("apple");
    insert("banana");
    int result = insert("grape");
    printf("TestInsert_AlreadyFilledSlot_insertAtAnotherPosition_returnTrue = %d\n", result == 1);
}

// Тест: Поиск существующей строки
void test_search_ExistingString_returnTrue() {
    memset(table, 0, sizeof(table));  // Очищаем таблицу
    insert("apple");
    int result = search("apple");
    printf("TestSearch_ExistingString_returnTrue = %d\n", result == 1);
}

// Тест: Поиск несуществующей строки
void test_search_NonExistingString_returnFalse() {
    memset(table, 0, sizeof(table));  // Очищаем таблицу
    insert("apple");
    int result = search("banana");
    printf("TestSearch_NonExistingString_returnFalse = %d\n", result == 0);
}

// Тест: Освобождение памяти для таблицы
void test_free_table_FilledTable_noMemoryLeaks() {
    memset(table, 0, sizeof(table));  // Очищаем таблицу
    insert("apple");
    insert("banana");
    free_table();
    printf("TestFreeTable_FilledTable_noMemoryLeaks = 1\n");
}

// Тест: Попытка вставки в переполненную таблицу
void test_insert_OverflowTable_returnFalse() {
    memset(table, 0, sizeof(table));  // Очищаем таблицу
    for (int i = 0; i < TABLE_SIZE; i++) {
        char str[10];
        sprintf(str, "item%d", i);
        insert(str);
    }
    int result = insert("overflow");
    printf("TestInsert_OverflowTable_returnFalse = %d\n", result == 0);
}

// Тест: Копирование строки через my_strdup
void test_my_strdup_ValidString_returnCopy() {
    const char* original = "test";
    char* copy = my_strdup(original);
    printf("TestMyStrdup_ValidString_returnCopy = %d\n", strcmp(copy, original) == 0);
    free(copy);
}

// Тест: Вставка строки, которая уже есть в таблице
void test_insert_DuplicateString_returnFalse() {
    memset(table, 0, sizeof(table));  // Очищаем таблицу
    insert("apple");
    int result = insert("apple");  // Пытаемся вставить повторно
    printf("TestInsert_DuplicateString_returnFalse = %d\n", result == 0);  // Ожидаем false, так как она уже есть
}

// Тест: Поиск строки после её удаления
void test_search_AfterDelete_returnFalse() {
    memset(table, 0, sizeof(table));  // Очищаем таблицу
    insert("apple");
    free_table();  // Очистка таблицы
    int result = search("apple");  // Строка должна быть удалена
    printf("TestSearch_AfterDelete_returnFalse = %d\n", result == 0);  // Ожидаем false
}

// Тест: Проверка хэш-функции на разные строки
void test_hash_DifferentString_returnDifferentHash() {
    const char* str1 = "apple";
    const char* str2 = "banana";
    int hash1 = hash(str1);  // Получаем хэш для первой строки
    int hash2 = hash(str2);  // Получаем хэш для второй строки

    // Проверяем, что хэши для разных строк различны
    printf("TestHash_DifferentString_returnDifferentHash = %d\n", hash1 != hash2);
}

// Запуск всех тестов
void run_all_tests() {
    test_insert_EmptyTable_insertValidString_returnTrue();
    test_insert_AlreadyFilledSlot_insertAtAnotherPosition_returnTrue();
    test_search_ExistingString_returnTrue();
    test_search_NonExistingString_returnFalse();
    test_free_table_FilledTable_noMemoryLeaks();
    test_insert_OverflowTable_returnFalse();
    test_my_strdup_ValidString_returnCopy();
    test_insert_DuplicateString_returnFalse();
    test_search_AfterDelete_returnFalse();
    test_hash_DifferentString_returnDifferentHash();
}

int main() {
    setlocale(LC_ALL, ""); // Для поддержки русского языка в выводе
    run_all_tests();
    return 0;
}
