#include <gtest/gtest.h>
#include "hashtable.h"

// Тест 1: Вставка в пустую хеш-таблицу
TEST(HashtableTest, InsertToEmptyTable_no1) {
    HashTable *ht = create_table();
    ASSERT_EQ(insert(ht, "test1", 100), 0);
    ASSERT_EQ(search(ht, "test1"), 100);
    destroy_table(ht);
}

// Тест 2: Вставка элемента с уже существующим ключом
TEST(HashtableTest, InsertDuplicateKey_no2) {
    HashTable *ht = create_table();
    ASSERT_EQ(insert(ht, "test1", 100), 0);
    ASSERT_EQ(insert(ht, "test1", 200), 0);  // Обновление значения
    ASSERT_EQ(search(ht, "test1"), 200);
    destroy_table(ht);
}

// Тест 3: Удаление элемента из таблицы
TEST(HashtableTest, RemoveElement_no3) {
    HashTable *ht = create_table();
    ASSERT_EQ(insert(ht, "test1", 100), 0);
    ASSERT_EQ(remove_entry(ht, "test1"), 0);
    ASSERT_EQ(search(ht, "test1"), -1); // После удаления элемент должен быть не найден
    destroy_table(ht);
}

// Тест 4: Удаление несуществующего элемента
TEST(HashtableTest, RemoveNonExistentElement_no4) {
    HashTable *ht = create_table();
    ASSERT_EQ(remove_entry(ht, "nonexistent"), -1);
    destroy_table(ht);
}

// Тест 5: Вставка элементов, пока не произойдет переполнение
TEST(HashtableTest, InsertUntilOverflow_no5) {
    HashTable *ht = create_table();
    for (int i = 0; i < TABLE_SIZE; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        ASSERT_EQ(insert(ht, key, i), 0);
    }
    ASSERT_EQ(insert(ht, "overflow", 100), -1); // Таблица переполнена
    destroy_table(ht);
}

// Тест 6: Поиск в пустой хеш-таблице
TEST(HashtableTest, SearchInEmptyTable_no6) {
    HashTable *ht = create_table();
    ASSERT_EQ(search(ht, "empty"), -1);
    destroy_table(ht);
}

// Тест 7: Вставка и проверка значения для нескольких элементов
TEST(HashtableTest, MultipleInsertions_no7) {
    HashTable *ht = create_table();
    for (int i = 0; i < 50; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        ASSERT_EQ(insert(ht, key, i), 0);
    }
    ASSERT_EQ(search(ht, "key49"), 49); // Проверка наличия ключа
    destroy_table(ht);
}

// Тест 8: Вывод хеш-таблицы (проверка корректности работы print_table)
TEST(HashtableTest, PrintTable_no8) {
    HashTable *ht = create_table();
    insert(ht, "key1", 100);
    insert(ht, "key2", 200);
    insert(ht, "key3", 300);
    print_table(ht);
    destroy_table(ht);
}

// Тест 9: Вставка элемента с длинным ключом
TEST(HashtableTest, InsertLongKey_no9) {
    HashTable *ht = create_table();
    char key[100];
    memset(key, 'a', 99); // Делаем ключ длиной 99 символов
    key[99] = '\0';
    ASSERT_EQ(insert(ht, key, 1000), 0);
    ASSERT_EQ(search(ht, key), 1000);
    destroy_table(ht);
}

// Тест 10: Проверка вставки и поиска на границе таблицы
TEST(HashtableTest, InsertAndSearchBoundary_no10) {
    HashTable *ht = create_table();
    char key[] = "boundarykey";
    ASSERT_EQ(insert(ht, key, 100), 0);
    ASSERT_EQ(search(ht, key), 100);
    destroy_table(ht);
}