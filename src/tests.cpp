extern "C" {
#include "lin_htable.h"
}

#include <gtest/gtest.h>

TEST(InsertTest, InsertNewValue_no1) {
    HashTable table = createTable(10);
    EXPECT_EQ(insert(&table, "apple"), INSERT_SUCCESS); // Вставлено
    freeTable(&table);
}

TEST(InsertTest, InsertDuplicateValue_no2) {
    HashTable table = createTable(10);
    insert(&table, "banana");
    EXPECT_EQ(insert(&table, "banana"), INSERT_FAIL); // Дубликат
    freeTable(&table);
}

TEST(InsertTest, InsertUntilFull_no3) {
    HashTable table = createTable(3);
    insert(&table, "a");
    insert(&table, "b");
    insert(&table, "c");
    EXPECT_EQ(insert(&table, "d"), INSERT_OVERFLOW); // Переполнена
    freeTable(&table);
}

TEST(SearchTest, SearchExisting_no4) {
    HashTable table = createTable(10);
    insert(&table, "grape");
    EXPECT_EQ(search(&table, "grape"), 1);
    freeTable(&table);
}

TEST(SearchTest, SearchNonExisting_no5) {
    HashTable table = createTable(10);
    insert(&table, "orange");
    EXPECT_EQ(search(&table, "melon"), 0);
    freeTable(&table);
}

TEST(DeleteTest, DeleteExisting_no6) {
    HashTable table = createTable(10);
    insert(&table, "kiwi");
    EXPECT_EQ(deleteEntry(&table, "kiwi"), 1);
    EXPECT_EQ(search(&table, "kiwi"), 0);
    freeTable(&table);
}

TEST(DeleteTest, DeleteNonExisting_no7) {
    HashTable table = createTable(10);
    insert(&table, "peach");
    EXPECT_EQ(deleteEntry(&table, "plum"), 0);
    freeTable(&table);
}

TEST(FreeTest, FreeEmptiedTable_no8) {
    HashTable table = createTable(10);
    freeTable(&table);
    EXPECT_EQ(table.entries, nullptr);
    EXPECT_EQ(table.capacity, 0);
}

TEST(FreeTest, FreeWithValues_no9) {
    HashTable table = createTable(10);
    insert(&table, "apple");
    insert(&table, "banana");
    freeTable(&table);
    EXPECT_EQ(table.entries, nullptr);
}

TEST(RehashTest, RehashPreservesValues_no10) {
    HashTable table = createTable(5);
    insert(&table, "alpha");
    insert(&table, "beta");
    insert(&table, "gamma");

    rehash(&table, 11);

    EXPECT_EQ(search(&table, "alpha"), 1);
    EXPECT_EQ(search(&table, "beta"), 1);
    EXPECT_EQ(search(&table, "gamma"), 1);

    freeTable(&table);
}